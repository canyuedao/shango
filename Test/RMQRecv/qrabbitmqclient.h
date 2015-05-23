#ifndef RABBITMQCLIENT_H
#define RABBITMQCLIENT_H

#include <QObject>
#include <QThread>
#include <QStringList>
#include <amqp.h>


class QRabbitMQClient : public QThread
{
    Q_OBJECT

private:
    explicit QRabbitMQClient(QObject *parent = 0);
    ~QRabbitMQClient();

signals:
    void error(QString msg);
    void connected();
    void closed();
    void message(QString msg);

public slots:

private:
    void run();
    void ConnectRabbitMQ();
    bool RecvMessage();
    bool AmqpError(amqp_rpc_reply_t x, const char *context);
    bool CreateQueue();
    bool CreateFanouts();


public:
    void Start();
    void Stop();

    static QRabbitMQClient* getInstance();

public:
    void setHost(QString host);
    QString getHost();
    void setPort(int port);
    int getPort();
    void setUser(QString user);
    QString getUser();
    void setPassword(QString password);
    QString getPassword();
    void setQueue(QString queue);
    QString getQueue();
    void setFanouts(QStringList& fanouts);
    QStringList getFanouts();

private:
    bool                    m_running;
    QString                 m_host;
    int                     m_port;
    QString                 m_user;
    QString                 m_password;
    QString                 m_queue;
    QStringList             m_fanouts;

    amqp_connection_state_t m_conn;
};

#endif // RABBITMQCLIENT_H
