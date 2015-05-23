#ifndef RABBITMQTEST_H
#define RABBITMQTEST_H

#include <QObject>

class RabbitMQTest : public QObject
{
    Q_OBJECT
public:
    explicit RabbitMQTest(QObject *parent = 0);
    ~RabbitMQTest();

signals:
    void error(QString err);
    void connected();
    void closed();
    void message(QString msg);

public slots:

};

#endif // RABBITMQTEST_H
