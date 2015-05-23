#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>

class QXmlRpcCall;

class NetworkManager : public QObject
{
    Q_OBJECT
private:
    explicit NetworkManager(QObject *parent = 0);
    ~NetworkManager();

signals:

public slots:

public:
    bool    InitNetwork(int type);
    int     GetSystemType();
    bool    Get(QString uri, QString& data);
    bool    PostJson(QString uri, QString json, QString& data);
    bool    ParseConfig(QString config, QString &db, QString &user, QString &pwd);

    bool    CheckNetwork();
    bool    Execute(QString& request, QString& response);

public:
    static NetworkManager* getInstance();

private:
    int                 m_systemType;
    QXmlRpcCall*        m_rpcCall;
};

#endif // NETWORKMANAGER_H
