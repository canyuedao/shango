#ifndef HEART_H
#define HEART_H

#include <QObject>
#include <QThread>

class Heart : public QThread
{
    Q_OBJECT
public:
    explicit Heart(QObject *parent = 0);
    ~Heart();

signals:
    void error(QString str);
    void info(QString str);
    void recv(int id, int sp);

public slots:

public:
    void run();
};

#endif // HEART_H
