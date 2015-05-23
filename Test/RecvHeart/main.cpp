#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "heart.h"

void InitLibPath(const char* argv0);

int main(int argc, char *argv[])
{
    char path[1024] = {0};
    strcpy(path, argv[0]);
    char* s = strrchr(path, '\\');
    if(NULL == s)
    {
        s = strrchr(path, '/');
        if(NULL != s)
        {
            *s = 0;
        }
    }
    else
    {
        *s = 0;
    }

    QString dir = QString(path) + QDir::separator() + "plugins";
    // QCoreApplication::setLibraryPaths(QCoreApplication::libraryPaths() << dir);
    QCoreApplication::setLibraryPaths(QStringList() << dir);
    // 显示
    QGuiApplication app(argc, argv);

    qmlRegisterType<Heart>("My", 1, 0, "Heart");

    QQmlApplicationEngine engine;
    QStringList list = engine.pluginPathList();
    //engine.setPluginPathList(QStringList() << (dir));
    //engine.setPluginPathList(QStringList() << (dir + "\\qml"));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

void InitLibPath(const char* argv0)
{

    // QQmlApplicationEngine::addPluginPath(dir);
}
