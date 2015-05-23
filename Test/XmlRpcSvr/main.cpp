#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "httpserver.h"




int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    HttpServer http;

    return app.exec();
}
