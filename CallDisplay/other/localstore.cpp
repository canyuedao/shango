#include "localstore.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

LocalStore::LocalStore(QObject *parent) : QObject(parent)
{
    InitDB();
}

LocalStore::~LocalStore()
{

}

// 单例模式
LocalStore* LocalStore::getInstance()
{
    static LocalStore* ins = NULL;

    if(NULL == ins)
    {
        ins = new LocalStore;
    }

    return ins;
}

// 初始化数据库
void LocalStore::InitDB()
{
    QString dbPath;
    // 初始化路径
#ifdef WIN32
    dbPath = QCoreApplication::applicationDirPath()
            + "/system.db";
#elif ANDROID
#else
#error "not support"
#endif
    // 打开数据库
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);
    if(false == m_db.open())
    {
        qDebug() << "open database " << dbPath << "failed";
        return;
    }

    // 检测数据库
    QSqlQuery query = m_db.exec("select pname,pvalue from system_config limit 1");
    if(0 == query.lastError().type())
    {
        return;
    }

    QString create = "create table system_config(\n"
            "pname varchar(128) primary key,\n"
            "pvalue varchar(256)\n"
            ")";
    query = m_db.exec(create);
    if(0 != query.lastError().type())
    {
        qDebug() << "create table system_config" << query.lastError().text();
        return;
    }
}

// 获取所有配置参
QMap<QString, QString> LocalStore::GetConfigures()
{
    QMap<QString, QString> ret;
    QString sql = "select pname, pvalue from system_config";
    QSqlQuery query;

    m_lock.lock();
    query = m_db.exec(sql);
    if(0 == query.lastError().type())
    {
        while(query.next())
        {
            ret.insert(query.value("pname").toString(),
                       query.value("pvalue").toString());
        }
    }

    m_lock.unlock();
    return ret;
}

// 获取配置参数
QString LocalStore::GetConfigure(QString name)
{
    QString ret;
    QString sql = QString("select pvalue from system_config "
                          " where pname='%1'").arg(name);
    QSqlQuery query;

    m_lock.lock();
    query = m_db.exec(sql);
    if(0 == query.lastError().type())
    {
        while(query.next())
        {
            ret = query.value("pvalue").toString();
            break;
        }
    }

    m_lock.unlock();
    return ret;
}

// 保存配置参数
bool LocalStore::SaveConfigure(QString name, QString value)
{
    bool ret = true;
    QString insert = QString("insert into system_config(pname,pvalue) values "
                             " ('%1', '%2')").arg(name).arg(value);
    QString update = QString("update system_config set pvalue='%1' where "
                             " pname='%2'").arg(value).arg(name);
    QSqlQuery query;

    m_lock.lock();
    query = m_db.exec(update);
    if(1 != query.numRowsAffected())
    {
        qDebug() << query.lastError().text();
        query = m_db.exec(insert);
        if(1 != query.numRowsAffected())
        {
            qDebug() << query.lastError().text();
            ret = false;
        }
    }

    m_lock.unlock();
    return ret;
}
