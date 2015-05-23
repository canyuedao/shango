#include "qrabbitmqclient.h"
#include <string.h>
#include <errno.h>
#include <QUuid>


////////////////////////////////////////////////////////////////////////
/// QRabbitMQClient
QRabbitMQClient::QRabbitMQClient(QObject *parent)
    : QThread(parent)
    , m_port(5672)
    , m_conn(NULL)
    , m_running(false)
{

}

QRabbitMQClient::~QRabbitMQClient()
{
}

// 执行线程
void QRabbitMQClient::run()
{
    // 创建conn
    m_conn = amqp_new_connection();
    if(NULL == m_conn)
    {
        emit error(QString("amqp_new_connection failed: %1")
                     .arg(strerror(errno)));
        return;
    }

    emit connected();
    ConnectRabbitMQ();
    emit closed();
    // 销毁
    amqp_connection_close(m_conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(m_conn);
}

// 连接并接收
void QRabbitMQClient::ConnectRabbitMQ()
{
    int sockfd;

    // 连接
    sockfd = amqp_open_socket(m_host.toUtf8().data(), m_port);
    if(sockfd < 0)
    {
        emit error(QString("connect %1:%2 failed: %3")
                     .arg(m_host)
                     .arg(m_port)
                     .arg(amqp_error_string(-sockfd)));
        return;
    }

    amqp_set_sockfd(m_conn, sockfd);
    // 登录
    if(AmqpError(amqp_login(m_conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN,
               m_user.toUtf8().data(), m_password.toUtf8().data()),
                 "Logging in"))
    {
        return;
    }

    // 打开channel
    if(false == CreateQueue()
            || false == CreateFanouts())
    {
        return;
    }

    // 开始接收数
    m_running = true;
    while(true)
    {
        if(false == RecvMessage())
        {
            break;
        }
    }

    m_running = false;
}

// 接收消息
bool QRabbitMQClient::RecvMessage()
{
    amqp_frame_t frame;
    int result;
    amqp_basic_deliver_t *d;
    amqp_basic_properties_t *p;
    size_t body_target;
    size_t body_received;
    int channelid = 1;

    amqp_maybe_release_buffers(m_conn);
    // 等待有消息接接入
    result = amqp_simple_wait_frame(m_conn, &frame);
    if( result < 0 )
    {
        return false;
    }

    // 判断消息类型
    if(AMQP_FRAME_METHOD != frame.frame_type)
    {
        return true;
    }

    channelid = frame.channel;
    d = (amqp_basic_deliver_t *) frame.payload.method.decoded;
    if(AMQP_BASIC_DELIVER_METHOD != frame.payload.method.id)
    {
        return true;
    }

    // 接收下一个数据
    result = amqp_simple_wait_frame(m_conn, &frame);
    if(result < 0)
    {
        return false;
    }

    if(AMQP_FRAME_HEADER != frame.frame_type)
    {
        emit error(tr("Expected header!"));
        return false;
    }

    // 判断是否同一个channel
    if(channelid != frame.channel)
    {
        emit error(tr("Not the same channel!"));
        return false;
    }

    // 接收所有数据
    QString buff;
    body_target = frame.payload.properties.body_size;
    body_received = 0;
    while(body_received < body_target)
    {
        result = amqp_simple_wait_frame(m_conn, &frame);
        if(result < 0)
        {
            break;
        }

        if(AMQP_FRAME_BODY != frame.frame_type)
        {
            emit error(tr("Expected body!"));
            return false;
        }

        if(channelid != frame.channel)
        {
            emit error(tr("Not the same channel!"));
            return false;
        }

        body_received += frame.payload.body_fragment.len;
        buff.append(QString::fromLatin1(
                        (char*)frame.payload.body_fragment.bytes,
                        frame.payload.body_fragment.len));
    }

    // 判断接收是否完整
    if(body_received != body_target)
    {
        return false;
    }

    emit message(buff);
    // 回应服务器
    amqp_basic_ack(m_conn, channelid, d->delivery_tag, 0);

    return true;
}

// 输出错误
bool QRabbitMQClient::AmqpError(amqp_rpc_reply_t x, char const *context)
{
    QString err;

    switch (x.reply_type)
    {
    case AMQP_RESPONSE_NORMAL:
      return false;

    case AMQP_RESPONSE_NONE:
        err = QString("%1: missing RPC reply type!").arg(context);
        break;

    case AMQP_RESPONSE_LIBRARY_EXCEPTION:
        err = QString("%1: %2")
                .arg(context)
                .arg(amqp_error_string(x.library_error));
        break;

    case AMQP_RESPONSE_SERVER_EXCEPTION:
        switch (x.reply.id)
        {
        case AMQP_CONNECTION_CLOSE_METHOD:
        {
            amqp_connection_close_t *m = (amqp_connection_close_t *) x.reply.decoded;
            QString str;
            str.fromUtf8((char *) m->reply_text.bytes, (int) m->reply_text.len);
            err = QString("%1: server connection error %2, message: %3")
                    .arg(context)
                    .arg(m->reply_code)
                    .arg(str);
            break;
        }
        case AMQP_CHANNEL_CLOSE_METHOD:
        {
            amqp_channel_close_t *m = (amqp_channel_close_t *) x.reply.decoded;
            QString str;
            str.fromUtf8((char *) m->reply_text.bytes, (int) m->reply_text.len);
            err = QString("%1: server channel error %2, message: %3")
                    .arg(context)
                    .arg(m->reply_code)
                    .arg(str);
            break;
        }
        default:
            err = QString("%1: unknown server error, method id %2")
                    .arg(context)
                    .arg(x.reply.id);
            break;
      }
      break;
    default:
        return false;
    }

    emit error(err);
    return true;
}

// 创建队列
bool QRabbitMQClient::CreateQueue()
{
    int     channel = 1;

    amqp_channel_open(m_conn, channel);
    if(AmqpError(amqp_get_rpc_reply(m_conn), "Opening channel"))
    {
        return false;
    }

    // 定义队列
    amqp_queue_declare(m_conn, channel, amqp_cstring_bytes(m_queue.toUtf8().data()),
                       0, 1, 0, 0, amqp_empty_table);
    if(AmqpError(amqp_get_rpc_reply(m_conn), "Declare queue"))
    {
        return false;
    }

    // 接收数据
    amqp_basic_qos(m_conn, channel, 0, 1, 0);
    amqp_basic_consume(m_conn, channel, amqp_cstring_bytes(m_queue.toUtf8().data()),
                       amqp_empty_bytes, 0, 0, 0, amqp_empty_table);
    if(AmqpError(amqp_get_rpc_reply(m_conn), "Consuming"))
    {
        return false;
    }

    return true;
}

// 创建订阅
bool QRabbitMQClient::CreateFanouts()
{
    int         channel = 2;
    QString     queue = QUuid::createUuid().toString();

    // 判断是否真的需要创建
    if(m_fanouts.count() < 1)
    {
        return true;
    }

    // 创建队列
    amqp_channel_open(m_conn, channel);
    if(AmqpError(amqp_get_rpc_reply(m_conn), "Opening channel"))
    {
        return false;
    }

    // 定义队列
    amqp_queue_declare(m_conn, channel, amqp_cstring_bytes(queue.toUtf8().data()),
                       0, 0, 1, 0, amqp_empty_table);
    if(AmqpError(amqp_get_rpc_reply(m_conn), "Declare queue"))
    {
        return false;
    }

    // 绑定队列
    for(int i = 0; i < m_fanouts.count(); i++)
    {
        const QString& exchange = m_fanouts.at(i);

        amqp_exchange_declare(m_conn, channel,
                              amqp_cstring_bytes(exchange.toUtf8().data()),
                              amqp_cstring_bytes("fanout"),
                              0, 1, 0, 0, amqp_empty_table);
        if(AmqpError(amqp_get_rpc_reply(m_conn), "Declare exchange"))
        {
            return false;
        }

        amqp_queue_bind(m_conn, channel,
                        amqp_cstring_bytes(queue.toUtf8().data()),
                        amqp_cstring_bytes(exchange.toUtf8().data()),
                        amqp_cstring_bytes(""),
                        amqp_empty_table);
        if(AmqpError(amqp_get_rpc_reply(m_conn), "Bind queue and exchange"))
        {
            return false;
        }
    }

    // 接收数据
    amqp_basic_qos(m_conn, channel, 0, 1, 0);
    amqp_basic_consume(m_conn, channel, amqp_cstring_bytes(queue.toUtf8().data()),
                       amqp_empty_bytes, 0, 0, 0, amqp_empty_table);
    if(AmqpError(amqp_get_rpc_reply(m_conn), "Consuming"))
    {
        return false;
    }

    return true;
}

// 开始执行
void QRabbitMQClient::Start()
{
    start();
}

// 退出
void QRabbitMQClient::Stop()
{
    if(NULL != m_conn)
    {
        amqp_connection_close(m_conn, AMQP_REPLY_SUCCESS);
    }
}

// 获取实例
QRabbitMQClient* QRabbitMQClient::getInstance()
{
    static QRabbitMQClient client;

    return &client;
}

void QRabbitMQClient::setHost(QString host)
{
    m_host = host;
}

QString QRabbitMQClient::getHost()
{
    return m_host;
}

void QRabbitMQClient::setPort(int port)
{
    m_port = port;
}

int QRabbitMQClient::getPort()
{
    return m_port;
}

void QRabbitMQClient::setUser(QString user)
{
    m_user = user;
}

QString QRabbitMQClient::getUser()
{
    return m_user;
}

void QRabbitMQClient::setPassword(QString password)
{
    m_password = password;
}

QString QRabbitMQClient::getPassword()
{
    return m_password;
}

void QRabbitMQClient::setQueue(QString queue)
{
    m_queue = queue;
}

QString QRabbitMQClient::getQueue()
{
    return m_queue;
}

void QRabbitMQClient::setFanouts(QStringList &fanouts)
{
    m_fanouts = fanouts;
}

QStringList QRabbitMQClient::getFanouts()
{
    return m_fanouts;
}
