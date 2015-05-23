#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QDebug>
#include <QtQml>
#include "rabbitmqtest.h"
#include "qrabbitmqclient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 注册类别
    qmlRegisterType<RabbitMQTest>("Shango", 1, 0, "RabbitMQTest");

    // 启动QML
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QRabbitMQClient* rmq = QRabbitMQClient::getInstance();
    rmq->setHost("192.168.0.221");
    rmq->setUser("shango");
    rmq->setPassword("admin");
    rmq->setQueue("queue.yj205");
    rmq->setFanouts(QStringList() << "k01" << "k02" << "k03" << "k04" << "k05");
    rmq->start();

    return app.exec();
}
