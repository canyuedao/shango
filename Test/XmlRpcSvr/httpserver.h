#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QThread>
#include <string>

struct event_base;
class HttpServer : public QThread
{
    Q_OBJECT

public:
    HttpServer();
    ~HttpServer();

private:
    void run();

    static void ResourceRead(const char* path, std::string& str);
    static void HttpRead(struct evhttp_request* req, std::string& str);
    static void HttpWriteError(struct evhttp_request* req, const char* fmt, ...);
    static void HttpWriteOk(struct evhttp_request* req, const char* fmt, ...);
    static void HttpWriteRes(struct evhttp_request* req, const char* res);
    static void WebXmlrpcCommon2(struct evhttp_request* req, void *arg);
    static void WebXmlRpcObject(struct evhttp_request* req, void *arg);
    static void WebConfig(struct evhttp_request* req, void *arg);
    static void WebGeneric(struct evhttp_request* req, void *arg);

private:
    struct event_base*  m_base;
};

#endif // HTTPSERVER_H
