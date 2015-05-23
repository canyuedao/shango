#ifndef CONFIGURECONTROLLER_H
#define CONFIGURECONTROLLER_H

#include <QObject>

class ConfigureController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
public:
    explicit ConfigureController(QObject *parent = 0);
    ~ConfigureController();

signals:
    void ipChanged();
    void portChanged();
    void typeChanged();

public slots:
    void saveConfigure();

public:
    QString ip();
    void setIp(QString ip);
    int port();
    void setPort(int port);
    int type();
    void setType(int type);

private:
    QString         m_ip;
    int             m_port;
    int             m_type;
};

#endif // CONFIGURECONTROLLER_H
