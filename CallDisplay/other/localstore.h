#ifndef LOCALSTORE_H
#define LOCALSTORE_H

#include <QObject>
#include <QMutex>
#include <QSqlDatabase>
#include <QMap>
#include <QString>

class LocalStore : public QObject
{
    Q_OBJECT
private:
    explicit LocalStore(QObject *parent = 0);
    ~LocalStore();

signals:

public slots:

public:
    static LocalStore* getInstance();

private:
    void        InitDB();

public:
    QMap<QString, QString> GetConfigures();
    QString GetConfigure(QString name);
    bool SaveConfigure(QString name, QString value);

private:
    QMutex              m_lock;
    QSqlDatabase        m_db;
};


#define CONFIG_DISPLAY_TYPE         "display_type"
#define CONFIG_SERVER_IP            "server_ip"
#define CONFIG_SERVER_PORT          "server_port"


#endif // LOCALSTORE_H
