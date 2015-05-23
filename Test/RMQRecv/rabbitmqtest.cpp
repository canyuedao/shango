#include "rabbitmqtest.h"
#include "qrabbitmqclient.h"

RabbitMQTest::RabbitMQTest(QObject *parent)
    : QObject(parent)
{
    connect(QRabbitMQClient::getInstance(), SIGNAL(message(QString)),
            this, SIGNAL(message(QString)));
    connect(QRabbitMQClient::getInstance(), SIGNAL(error(QString)),
            this, SIGNAL(error(QString)));
    connect(QRabbitMQClient::getInstance(), SIGNAL(connected()),
            this, SIGNAL(connected()));
    connect(QRabbitMQClient::getInstance(), SIGNAL(closed()),
            this, SIGNAL(closed()));
}

RabbitMQTest::~RabbitMQTest()
{

}

