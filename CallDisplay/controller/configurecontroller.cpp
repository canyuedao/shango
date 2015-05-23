#include "configurecontroller.h"
#include "../other/localstore.h"

ConfigureController::ConfigureController(QObject *parent) : QObject(parent)
{
    m_ip = LocalStore::getInstance()->GetConfigure(CONFIG_SERVER_IP);
    m_port = LocalStore::getInstance()->GetConfigure(CONFIG_SERVER_PORT).toInt();
    m_type = LocalStore::getInstance()->GetConfigure(CONFIG_DISPLAY_TYPE).toInt();
}

ConfigureController::~ConfigureController()
{

}

QString ConfigureController::ip()
{
    return m_ip;
}

void ConfigureController::setIp(QString ip)
{
    m_ip = ip;
}

int ConfigureController::port()
{
    return m_port;
}

void ConfigureController::setPort(int port)
{
    m_port = port;
}

int ConfigureController::type()
{
    return m_type;
}

void ConfigureController::setType(int type)
{
    m_type = type;
}

// 保存设置
void ConfigureController::saveConfigure()
{
    LocalStore::getInstance()->SaveConfigure("server_ip", m_ip);
    LocalStore::getInstance()->SaveConfigure("server_port", QString::number(m_port));
    LocalStore::getInstance()->SaveConfigure("display_type", QString::number(m_type));
}
