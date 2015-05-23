#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QFuture>

class MainController : public QObject
{
    Q_OBJECT

public:
    explicit MainController(QObject *parent = 0);
    ~MainController();

signals:
    void login(int type);

public slots:
    void start();
    void reconnect();

private:
    void InitSystem();

private:
    QFuture<void>      m_init;
};

#endif // MAINCONTROLLER_H
