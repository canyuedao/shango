#include "heart.h"
#include <boost/bind.hpp>
#include <string.h>

class Node
{
public:
    Node(boost::asio::io_service& ios)
        : sock(ios)
    {
    }

public:
    boost::asio::ip::tcp::socket            sock;
    char                                    buffer[1024];
    std::string                             data;
};

Heart::Heart(QObject *parent)
    : QThread(parent)
{
    start();

}

Heart::~Heart()
{

}

// 分析数据
int ParseData(Heart* h, const char* data, size_t len)
{
    // 包长度不足
    if(len <= 2)
    {
        return 0;
    }

    // 不是我们的包
    if(0xFE != (unsigned char)*data)
    {
        emit h->error(QString("error protocol"));
        return -1;
    }

    // 判断长度
    int n = (unsigned char)*(data + 1) & 0x000000ff;
    if(len < n)
    {
        return 0;
    }

    int id = (unsigned char)ntohs(*((short *)(data + 2))) & 0x0000ffff;
    int sp = (unsigned char)*(data + n - 1) & 0x000000ff;

    emit h->recv(id, sp);
    return n;
}

// 接收数据
void MyRecv(Heart* h, Node *node,
            boost::system::error_code ec,
            size_t len)
{
    if(ec)
    {
        emit h->error(QString("disconnect"));
        delete node;
        return;
    }

    // 接收数据
    node->data.append(node->buffer, len);
    // 分析数据
    int ret = 0;
    do
    {
        ret = ParseData(h, node->data.c_str(), node->data.size());
        if(ret > 0 && ret <= node->data.size())
        {
            node->data.erase(node->data.begin(), node->data.begin() + ret);
        }
        else if(-1 == ret)
        {
            delete node;
            return;
        }
    } while(0 != ret);

    // 接收数据
    node->sock.async_receive(boost::asio::buffer(node->buffer, sizeof(node->buffer)),
                        boost::bind(&MyRecv, h, node, _1, _2));
}

// 接收连接
void MyAccept(Heart* h,
              boost::asio::ip::tcp::acceptor *accept,
              Node *node,
              boost::system::error_code ec)
{
    if(ec)
    {
        emit h->error(QString("%1").arg(ec.message().c_str()));
        return;
    }

    // 接收数据
    node->sock.async_receive(boost::asio::buffer(node->buffer, sizeof(node->buffer)),
                        boost::bind(&MyRecv, h, node, _1, _2));
    emit h->info(QString("connected"));

    // 下一个接收
    Node *next = new Node(node->sock.get_io_service());
    accept->async_accept(next->sock, boost::bind(&MyAccept, h, accept, next, _1));
}

void Heart::run()
{
    boost::asio::ip::tcp::acceptor  *accept;
    boost::asio::ip::address_v4 addr(0);
    boost::asio::ip::tcp::endpoint	ep(addr, 9010);

    accept = new boost::asio::ip::tcp::acceptor(m_ios, ep);
    if(NULL == accept)
    {
        emit error(QString("Listen error"));
        return;
    }

    Node *node = new Node(m_ios);
    accept->async_accept(node->sock, boost::bind(&MyAccept, this, accept, node, _1));

    emit info(QString("start listen"));
    m_ios.run();
    emit error(QString("end"));
}

void Heart::Stop()
{
    m_ios.stop();
    wait();
}

