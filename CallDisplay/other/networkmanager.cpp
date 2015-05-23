#include "networkmanager.h"
#include <qxmlrpccall.h>
#include "localstore.h"
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , m_systemType(0)
{
    m_rpcCall = NULL;
}

NetworkManager::~NetworkManager()
{
    if(NULL != m_rpcCall) delete m_rpcCall;
}

// 单例模式
NetworkManager* NetworkManager::getInstance()
{
    static NetworkManager *ins = NULL;

    if(NULL == ins)
    {
        ins = new NetworkManager();
    }

    return ins;
}

// 初始化系统
bool NetworkManager::InitNetwork(int type)
{
    if(NULL != m_rpcCall)
    {
        delete m_rpcCall;
    }

    // 初始化rcp
    QString ip = LocalStore::getInstance()->GetConfigure(CONFIG_SERVER_IP);
    QString port = LocalStore::getInstance()->GetConfigure(CONFIG_SERVER_PORT);
    // 从服务器获取配置
    QString config;
    if(false == PostJson(QString("http://%1:%2/web/get_supper/user_info")
                         .arg(ip).arg(port),
                         "{}",
                         config))
    {
        return false;
    }

    // 解析数据
    QString     db;
    QString     user;
    QString     pwd;

    if(false == ParseConfig(config, db, user, pwd))
    {
        return false;
    }

    //
    m_rpcCall = new QXmlRpcCall(ip, port.toInt(), db);

    // 登录服务器
    return m_rpcCall->Login(user, pwd, QString::number(type));
}

// 获取系统显示的类别
int NetworkManager::GetSystemType()
{
    return m_systemType;
}

// 从网页获取数据
bool NetworkManager::Get(QString uri, QString &data)
{
    QNetworkAccessManager       manager;
    QNetworkRequest             httpGet;
    QNetworkReply               *reply;
    QEventLoop                  loop;

    httpGet.setUrl(uri);
    reply = manager.get(httpGet);
    if(NULL == reply)
    {
        return false;
    }

    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*))
                     , &loop, SLOT(quit()));
    loop.exec();
    // 处理接收数据
    data = QString::fromUtf8(reply->readAll());

    return true;
}

bool NetworkManager::PostJson(QString uri, QString json, QString &data)
{
    QNetworkAccessManager       manager;
    QNetworkRequest             httpPost;
    QNetworkReply               *reply;
    QEventLoop                  loop;

    httpPost.setUrl(uri);
    httpPost.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    reply = manager.post(httpPost, json.toUtf8());
    if(NULL == reply)
    {
        return false;
    }

    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*))
                     , &loop, SLOT(quit()));
    loop.exec();
    // 处理接收数据
    data = QString::fromUtf8(reply->readAll());
    return true;
}

// 解析配置文件
bool NetworkManager::ParseConfig(QString config,
                                 QString &db,
                                 QString &user,
                                 QString &pwd)
{
    QJsonDocument doc = QJsonDocument::fromJson(config.toUtf8());
    QJsonObject obj = doc.object();
    QJsonObject res;
    QJsonObject::iterator item;

    item = obj.find("result");
    if(obj.end() == item)
    {
        return false;
    }

    res = item.value().toObject();
    item = res.find("password");
    if(item != res.end())
    {
        db = item.value().toString();
        //pwd = item.value().toString();
    }

    item = res.find("db_name");
    if(item != res.end())
    {
        user = item.value().toString();
        //db = item.value().toString();
    }

    item = res.find("user");
    if(item != res.end())
    {
        pwd = item.value().toString();
        //user = item.value().toString();
    }

    return true;
}


// 检测网络状态
bool NetworkManager::CheckNetwork()
{
    return true;
}

bool NetworkManager::Execute(QString &request, QString &response)
{
    if(NULL == m_rpcCall)
    {
        return false;
    }

    return m_rpcCall->Execute(request, response);
}


