#include "maincontroller.h"
#include <QDebug>
#include <QtConcurrent>
#include "../other/networkmanager.h"
#include "../other/localstore.h"

MainController::MainController(QObject *parent) : QObject(parent)
{

}

MainController::~MainController()
{

}

// [槽] 开始业务逻辑
void MainController::start()
{
    if( m_init.isFinished() )
    {
        qDebug() << "MainController::start" << "[start]";
        m_init = QtConcurrent::run(this, &MainController::InitSystem);
    }
}

void MainController::reconnect()
{
    qDebug() << "MainController::reconnect";
}

/*
 * 初始化系统
 * 初始化成功以后一定要发送login信号
 */
void MainController::InitSystem()
{
    int systemType;
    bool isOk;

    // 获取服务器类型
    systemType = LocalStore::getInstance()->GetConfigure(CONFIG_DISPLAY_TYPE).toInt();
    if(0 == systemType)
    {
        emit login(0);
        return;
    }

    // 从服务器初始化环境
    isOk = NetworkManager::getInstance()->InitNetwork(systemType);
    emit login( (isOk) ? systemType : -1 );
}

