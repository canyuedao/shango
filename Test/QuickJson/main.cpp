#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "quickjson.h"
#include <QDebug>

#include <QHostInfo>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QString localIp;
    QString localhostName=QHostInfo::localHostName();
    QHostInfo info=QHostInfo::fromName(localhostName);
    foreach(QHostAddress address,info.addresses())
    {
      if(address.protocol()==QAbstractSocket::IPv4Protocol){
        qDebug()<<address.toString(); //输出IPV4的地址
        localIp = address.toString();
      }
    }

    //QuickJson  json;
    QuickJson infusObj;
    infusObj.ValueSet("version",1.0);
    infusObj.ValueSet("contentype","");
    infusObj.ValueSet("sender",localIp);
    infusObj.ArrayAdd("receiver","");
    infusObj.ValueSet("timestamp",0);
    infusObj.ValueSet("live",0);
    infusObj.ValueSet("data.funcid",600002);
    infusObj.ValueSet("data.rescode",0);
    infusObj.ValueSet("data.resdesc",0);

    infusObj.ArrayAdd("data.msg.state",1);
    infusObj.ValueSet("data.msg.current_page",1);
    infusObj.ValueSet("data.msg.pate_size",22);
    infusObj.ValueSet("data.msg.sub_number","订阅号");

    //infusObj.ArrayAdd("data.msg",msgObj.toJson());
    infusObj.ValueSet("digest",0);
    infusObj.ValueSet("signature",0);

    qDebug() << infusObj.toJson();

    /*
    json.ValueSet("data.condition", "102");
    json.ValueSet("data.current_page", 0);

    json.ArrayAdd("data.state", -1);
    json.ArrayAdd("data.state", 1);


    qDebug() << json.toJson();
*/

    const char* str = "{\n"
                      "\"data\": {\n"
                      "    \"condition\": \"021\",\n"
                      "    \"current_page\": 1,\n"
                      "    \"page_size\": 2,\n"
                      "    \"state\": [\n"
                      "        -1,\n"
                      "        1\n"
                      "    ],\n"
                      "    \"sub_numbers\": [\n"
                      "        \"aa\"\n"
                      "    ]\n"
                      "},\n"
                      "\"funcid\": \"99999999\",\n"
                      "\"rescode\": 0,\n"
                      "\"resdesc\": 0,\n"
                      "\"sender\": \"192.168.0.7\",\n"
                      "\"tag\": 0,\n"
                      "\"timestamp\": 0\n"
                      "}";

    infusObj.Parse(str);

    QJsonValue val1 = infusObj.ValueGet("data.condition");
    QJsonValue val2 = infusObj.ValueGet("funcid");

    qDebug() << val1.toString() << val2;


    return app.exec();
}
