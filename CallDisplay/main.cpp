#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QDir>
#include <QFontDatabase>
#include <QtQml>
#include "controller/maincontroller.h"
#include "controller/transfusecontroller.h"
#include "controller/configurecontroller.h"
#include "other/localstore.h"
#include "other/networkmanager.h"
#include "other/globalobject.h"

#define DEVELOP         1

void InitSystem();
void InitQMLType();
void InitFonts();

int main(int argc, char *argv[])
{
    // 配置系统环境
    InitSystem();
    // 申名APP对像
    QGuiApplication app(argc, argv);

    // 注册QML类, 工程以UI驱动C++代码，而非C++驱动UI
    InitQMLType();

    // 实例化对像
    NetworkManager::getInstance();
    LocalStore::getInstance();

    // 安装字体
    InitFonts();
    // 加载主QML
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("cpp", GlobalObject::getInstance());
#if DEVELOP
    engine.load(QUrl(QStringLiteral("qml/MainDevelop.qml")));
#else
    engine.load(QUrl(QStringLiteral("qrc:/qml/Main.qml")));
#endif

    return app.exec();
}

// 安装字体
void InitFonts()
{
#if DEVELOP
        // 设置工作目录
        qDebug() << "Current Directory: " << __PROJECT__ << "/res";
        QDir::setCurrent(QString("%1/res").arg(__PROJECT__));
        // 安装字体
        int id = QFontDatabase::addApplicationFont(QObject::tr("other/FZLTCHK.ttf"));
        QStringList list = QFontDatabase::applicationFontFamilies(id);
        for(int a = 0; a < list.count(); a++)
        {
            // FZLanTingHei-B-GBK
            qDebug("Font: %s", list.at(a).toUtf8().data());
        }

#else
    // 安装字体
        int id = QFontDatabase::addApplicationFont(":/other/FZLTCHK.TTF");
        QStringList list = QFontDatabase::applicationFontFamilies(id);
        for(int a = 0; a < list.count(); a++)
        {
            qDebug("Font: %s", list.at(a).toUtf8().data());
        }

#endif
}

// 实始化环境信息
void InitSystem()
{
}

// 注册QML对像
// 整个工程是以界面驱动逻辑，而非逻辑驱动界面
void InitQMLType()
{
    // 注册主控制器
    qmlRegisterType<MainController>("Shango", 1, 0, "MainController");
    // 注册配置页面
    qmlRegisterType<ConfigureController>("Shango", 1, 0, "ConfigureController");
    // 注册输液控制器
    qmlRegisterType<TransfuseController>("Shango", 1, 0, "TransfuseController");

}


