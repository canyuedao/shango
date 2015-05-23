#ifndef ENVOBJECT_H
#define ENVOBJECT_H

#include <QObject>

class GlobalObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int switchinterval READ switchinterval NOTIFY switchintervalChange)
    Q_PROPERTY(QString bottomTitleString READ bottomTitleString NOTIFY bottomTitleStringChange)
private:
    explicit GlobalObject(QObject *parent = 0);
    ~GlobalObject();

signals:
    void switchintervalChange();
    void bottomTitleStringChange();

public slots:

public:
    int switchinterval();
    QString bottomTitleString();

public:
    static GlobalObject* getInstance();

public:
    QString str;        // 滚动字幕
};

#endif // ENVOBJECT_H
