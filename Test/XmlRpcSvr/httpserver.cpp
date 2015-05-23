#include "httpserver.h"
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>
#include <string>
#include <QFile>
#include <QDebug>

HttpServer::HttpServer()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2) , &wsaData);

    m_base = event_base_new();
    start();
}

HttpServer::~HttpServer()
{
    if(NULL != m_base)
    {
        this->terminate();
        event_base_free(m_base);
        m_base = NULL;
    }
}

void HttpServer::run()
{
    int                 ret;
    struct evhttp       *http;

    http = evhttp_new(m_base);
    if(NULL == http)
    {
        return;
    }

    ret = evhttp_bind_socket(http, "0.0.0.0", 9000);
    if(0 != ret)
    {
        return;
    }

    evhttp_set_cb(http, "/xmlrpc/common2", &HttpServer::WebXmlrpcCommon2, this);
    evhttp_set_cb(http, "/xmlrpc/object", &HttpServer::WebXmlRpcObject, this);
    evhttp_set_cb(http, "/web/get_supper/user_info", &HttpServer::WebConfig, this);
    evhttp_set_gencb(http, &HttpServer::WebGeneric, this);
    // 事件循环中
    event_base_dispatch(m_base);
    // 释放资源
    evhttp_free(http);
}

void HttpServer::ResourceRead(const char *path, std::string &str)
{
    QFile   fp(path);

    if(fp.open(QIODevice::ReadOnly))
    {
        str.append(fp.readAll().data());
        fp.close();
    }
}

void HttpServer::HttpRead(evhttp_request *req, std::string &str)
{
    struct evbuffer *buf = evhttp_request_get_input_buffer(req);
    size_t  len = evbuffer_get_length(buf);

    str.resize(len, 0);
    evbuffer_remove(buf, (char *)str.c_str(), len);
}

void HttpServer::HttpWriteError(evhttp_request *req, const char *fmt, ...)
{
    struct evbuffer *buf = evbuffer_new();
    va_list     va;

    va_start(va, fmt);
    evbuffer_add_vprintf(buf, fmt, va);
    va_end(va);

    evhttp_send_reply(req, HTTP_INTERNAL, "Internal Server Error", buf);
    evbuffer_free(buf);
}

void HttpServer::HttpWriteOk(evhttp_request *req, const char *fmt, ...)
{
    struct evbuffer *buf = evbuffer_new();
    va_list     va;

    va_start(va, fmt);
    evbuffer_add_vprintf(buf, fmt, va);
    va_end(va);

    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    evbuffer_free(buf);
}

void HttpServer::HttpWriteRes(evhttp_request *req, const char *res)
{
    std::string str;

    ResourceRead(res, str);
    HttpWriteOk(req, "%s", str.c_str());
}

void HttpServer::WebXmlrpcCommon2(struct evhttp_request* req, void *arg)
{
    if( EVHTTP_REQ_POST != evhttp_request_get_command(req) )
    {
        HttpWriteError(req, "Error request method!");
        return;
    }

    std::string buf;
    HttpRead(req, buf);
    // 处理回应
    if(NULL != strstr(buf.c_str(), "<methodName>login</methodName>"))
    {
        HttpWriteRes(req, ":/data/login.xml");
    }
    else
    {
        HttpWriteError(req, "Can not find function");
    }
}

void HttpServer::WebXmlRpcObject(struct evhttp_request* req, void *arg)
{
    if( EVHTTP_REQ_POST != evhttp_request_get_command(req) )
    {
        HttpWriteError(req, "Error request method!");
        return;
    }

    std::string buf;
    HttpRead(req, buf);
    // 处理回应
    if(NULL != strstr(buf.c_str(), "<methodName>execute</methodName>"))
    {
        HttpWriteRes(req, ":/data/wait_queue.xml");
    }

    qDebug() << buf.c_str();
}

void HttpServer::WebConfig(evhttp_request *req, void *arg)
{
    HttpWriteRes(req, ":/data/config.json");
}

void HttpServer::WebGeneric(struct evhttp_request* req, void *arg)
{
    HttpWriteOk(req, "This is a xmlrpc server sample test!");
}


