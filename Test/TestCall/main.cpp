#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QFontDatabase>
#include <QTextStream>

// #define DESIGN  // 设计标志

void InitFont();
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

#ifndef DESIGN
    // 安装字体
    int id = QFontDatabase::addApplicationFont(":/fonts/FZLTCHK.TTF");
    QStringList list = QFontDatabase::applicationFontFamilies(id);
    for(int a = 0; a < list.count(); a++)
    {
        qDebug("Font: %s", list.at(a).toUtf8().data());
    }

    // 显示QML
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
#else
    // 设置工作目录
    QDir::setCurrent(QObject::tr("D:\\yuanjie\\SVN\\shango\\Test\\TestCall\\res"));
    // 安装字体
    int id = QFontDatabase::addApplicationFont(QObject::tr("fonts/FZLTCHK.ttf"));
    QStringList list = QFontDatabase::applicationFontFamilies(id);
    for(int a = 0; a < list.count(); a++)
    {
        // FZLanTingHei-B-GBK
        qDebug("Font: %s", list.at(a).toUtf8().data());
    }

    // 显示QML
    QQmlApplicationEngine engine;
    engine.load(QUrl("qml/main.qml"));
#endif // TEST

    return app.exec();
}
