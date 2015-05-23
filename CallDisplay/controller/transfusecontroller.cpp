#include "transfusecontroller.h"
#include <QtConcurrent>
#include <QDebug>
#include "../model/commonmodel.h"
#include <math.h>
#include "../other/networkmanager.h"
#include "../other/analysisjson.h"
TransfuseController::TransfuseController(QObject *parent) : QObject(parent)
{

    InitModel();

    m_heart.start();
    connect(&m_heart, SIGNAL(recv(int,int)),
            this, SLOT(onMonitorRecv(int,int)));
}

TransfuseController::~TransfuseController()
{
    m_futureInfusionQueue.waitForFinished();
    m_futureDoctorQueue.waitForFinished();
    m_futureNowSeeDoctorQueue.waitForFinished();
    m_futureOverQueue.waitForFinished();

    m_heart.Stop();
//    delete m_modelInfusionQueue;
//    delete m_modelDoctorQueue;
//    delete m_modelNowSeeDoctorQueue;
//    delete m_modelOverQueue;
//    delete m_bottomSubtitleQueue;
}


void TransfuseController::InitModel(){
    /* 初始化输液排队模型 */
    QHash<int, QByteArray>  rolesInfusion;
    rolesInfusion[CommonModel::RoleColumn0] = "sid";
    rolesInfusion[CommonModel::RoleColumn1] = "name";
    rolesInfusion[CommonModel::RoleColumn2] = "status";
    m_modelInfusionQueue = new CommonModel(rolesInfusion);

    /* 初始化医生简介模型 */
    QHash<int, QByteArray>  rolesDoctor;
    rolesDoctor[CommonModel::RoleColumn0] = "doctor_name";        // 医生姓名
    rolesDoctor[CommonModel::RoleColumn1] = "job_name";           // 医生职称
    rolesDoctor[CommonModel::RoleColumn2] = "office_name";        // 医生所属科室
    rolesDoctor[CommonModel::RoleColumn3] = "portrait";           // 医生头像
    m_modelDoctorQueue = new CommonModel(rolesDoctor);

    /* 初始化当前就诊信息模型 */
    QHash<int, QByteArray>  rolesNowSeeDoctor;
    rolesNowSeeDoctor[CommonModel::RoleColumn0] = "userName";     // 病人姓名
    rolesNowSeeDoctor[CommonModel::RoleColumn1] = "do_thing";     // 就诊名称
    m_modelNowSeeDoctorQueue = new CommonModel(rolesNowSeeDoctor);

    /* 初始化过号信息模型 */
    QHash<int, QByteArray>  rolesOverNumber;
    rolesOverNumber[CommonModel::RoleColumn0] = "patientName";    // 病人姓名
    rolesOverNumber[CommonModel::RoleColumn1] = "over_thing";     // 过号就诊名称
    m_modelOverQueue = new CommonModel(rolesOverNumber);

    /* 初始化滴速检测信息模型 */
    QHash<int, QByteArray>  rolesDropSpeedTest;
    rolesDropSpeedTest[CommonModel::RoleColumn0] = "sid";
    rolesDropSpeedTest[CommonModel::RoleColumn1] = "name";
    rolesDropSpeedTest[CommonModel::RoleColumn2] = "dropStatus";
    m_modeldropSpeedTestQueue = new CommonModel(rolesDropSpeedTest);

}

// 获取输液排队模型
QObject* TransfuseController::modelInfusionQueue()
{
    return m_modelInfusionQueue;
}

// 获取医生信息模型
QObject* TransfuseController::modelDoctorQueue()
{
    return m_modelDoctorQueue;
}

// 获取当前就诊模型
QObject* TransfuseController::modelNowSeeDoctorQueue()
{
    return m_modelNowSeeDoctorQueue;
}

// 获取过号模型
QObject* TransfuseController::modelOverQueue()
{
    return m_modelOverQueue;
}

// 获取滴速检测模型
QObject* TransfuseController::modelDropSpeedTestQueue()
{
    return m_modeldropSpeedTestQueue;
}


// 更新输液排队队列
void TransfuseController::upInfusionQueueModel( int page)
{
    if(false == m_futureInfusionQueue.isRunning())
    {
        m_futureInfusionQueue = QtConcurrent::run(this, &TransfuseController::RunUpdateInfusionQueueModel, page);
    }
}

// 更新医生信息队列
void TransfuseController::upDoctorQueueModel( int page)
{

    if(false == m_futureDoctorQueue.isRunning())
    {
        m_futureDoctorQueue = QtConcurrent::run(this,
                            &TransfuseController::RunUpdateDoctorQueueModel,
                            page);
    }
}

// 更新当前就诊队列
void TransfuseController::upNowSeeDoctorQueueModel( int page)
{
    if(false == m_futureNowSeeDoctorQueue.isRunning())
    {
        m_futureNowSeeDoctorQueue = QtConcurrent::run(this,
                          &TransfuseController::RunUpdateNowSeeDoctorQueueModel,
                           page);
    }
}

// 更新过号队列
void TransfuseController::upOverQueueModel( int page)
{
    if(false == m_futureOverQueue.isRunning())
    {
        m_futureOverQueue = QtConcurrent::run(this,
                                &TransfuseController::RunUpdateOverQueueModel,
                                 page);
    }
}

// 更新滴速检测队列
void TransfuseController::upDropSpeedTestQueueModel( int page)
{
    if(false == m_futureDropSpeedTestQueue.isRunning())
    {
        m_futureDropSpeedTestQueue = QtConcurrent::run(this,
                         &TransfuseController::RunUpdateDropSpeedTestQueueModel,
                          page);
    }
}

// 接收到心跳数据
void TransfuseController::onMonitorRecv(int id, int sp)
{
    m_monitorLock.lock();
    m_monitorData[id].speed = sp;
    m_monitorData[id].time = time(NULL);
    m_monitorLock.unlock();
}

// [线程]在线程中更新《输液》队列
// ***在这里要完成到服务器的数据请求
void TransfuseController::RunUpdateInfusionQueueModel(int page)
{
    // 模拟登录
    qDebug() << "add data";
    QThread::sleep(1);

    // 只有三页数据
    if(page > 2)
    {
        emit dataLoadComplate(Queue, -1);
        return;
    }

    m_modelInfusionQueue->BeginAdd();

    if(0 == page){
        for(int i=0;i<11;i++){
            m_modelInfusionQueue->Add(CommonModelItem("A001", "张三", "输液"));
            m_modelInfusionQueue->Add(CommonModelItem("A002", "李四", "等待输液"));
        }
    }else if(1 == page){
        for(int i=0;i<11;i++){
            m_modelInfusionQueue->Add(CommonModelItem("A003", "钱五百", "等待输液"));
            m_modelInfusionQueue->Add(CommonModelItem("A004", "蒋老师", "输液"));
        }
    }else {
        for(int i=0;i<8;i++){
            m_modelInfusionQueue->Add(CommonModelItem("A005", "王科长", "输液"));
            m_modelInfusionQueue->Add(CommonModelItem("A006", "田大宝", "等待输液"));
        }
    }

    m_modelInfusionQueue->EndAdd();
    emit dataLoadComplate(Queue, 0);
    qDebug() << "TransfuseController::RunUpdateInfusionQueueModel: " << page;

}

// [线程]在线程中更新《医生信息》队列
// ***在这里要完成到服务器的数据请求
void TransfuseController::RunUpdateDoctorQueueModel(int page)
{
    // 模拟登录
    qDebug() << "add data";
    QThread::sleep(1);

    // 只有两页数据
    if(page > 1)
    {
        emit dataLoadComplate(Doctor, -1);
        return;
    }

    m_modelDoctorQueue->BeginAdd();
    switch (page) {
    case 0:
        for(int i=0; i<4;i++){
            m_modelDoctorQueue->Add(CommonModelItem("列晓峰",
                                                    "主任医师",
                                                    "内科",
                                                    "../../image/doctor1.png"
                                                    ));
            m_modelDoctorQueue->Add(CommonModelItem("王树立",
                                                    "主任医师",
                                                    "内科",
                                                    "../../image/doctor2.png"
                                                    ));
        }
        break;
    case 1:
        for(int i=0; i<4;i++){
            m_modelDoctorQueue->Add(CommonModelItem("王树立", "主任医师", "内科", "../../image/doctor2.png"));
            m_modelDoctorQueue->Add(CommonModelItem("列晓峰","主任医师", "内科", "../../image/doctor1.png" ));
        }
        break;
    default:
        break;
    }

    m_modelDoctorQueue->EndAdd();
    emit dataLoadComplate(Doctor, 0);
    qDebug() << "TransfuseController::RunUpdateDoctorQueueModel";
}

// [线程]在线程中更新《当前就诊》队列
// ***在这里要完成到服务器的数据请求
void TransfuseController::RunUpdateNowSeeDoctorQueueModel(int page)
{
    // 模拟登录
    qDebug() << "add data";
    QThread::sleep(1);

    m_modelNowSeeDoctorQueue->BeginAdd();

    m_modelNowSeeDoctorQueue->Add(CommonModelItem("张大宝","输液" ));
    m_modelNowSeeDoctorQueue->Add(CommonModelItem("小花","输液"));

    m_modelNowSeeDoctorQueue->EndAdd();
    emit dataLoadComplate(NowSee, 0);
    qDebug() << "TransfuseController::RunUpdateNowSeeDoctorQueueModel";
}

// [线程]在线程中更新《过号》队列
// ***在这里要完成到服务器的数据请求
void TransfuseController::RunUpdateOverQueueModel(int page)
{
    // 模拟登录
    qDebug() << "add data";
    QThread::sleep(1);


    AnalysisJson analysisJson;
    QString req=analysisJson.genRequestJson(600002);
    // 只有两页数据
    qDebug()<<req;
    QString res;
    NetworkManager::getInstance()->Execute(req,res);
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(res.toUtf8(),&err);
    if(QJsonParseError::NoError != err.error){
        emit dataLoadComplate(OverQueue,-1);
        return;
    }
//    if(page > 1)
//    {
//        emit dataLoadComplate(OverQueue, -1);
//        return;
//    }
    qDebug()<<res;
    QJsonArray arr=doc.array();

    //QJsonValue val=infusObj.ValueGet("{}");
//    QJsonValue val=infusObj.toJson();
//    qDebug()<<val;
//    QJsonArray arr=val.toArray();

    int resCount=arr.count();
    int pgCount=(resCount%4)?(resCount/4):(resCount/4-1);
    if(page>pgCount){
        emit dataLoadComplate(OverQueue,-1);
        return;
    }
    m_modelOverQueue->BeginAdd();

    for(int i=0;i<4;i++){
        //infusObj.Parse(arr.at(i).toString());
        if(page*4+i<resCount){
            QJsonObject obj=arr[page*4+i].toObject();
            QString internalCode=obj["internal_code"].toString();
            QString name=obj["name"].toString();
            m_modelOverQueue->Add(CommonModelItem(internalCode,name));
        }

        //while(i<(page+1)*4){


        //}

    }

//    if(0 == page){
//        //arr.at(0).toString();
//        m_modelOverQueue->Add(CommonModelItem("" ));
//        m_modelOverQueue->Add(CommonModelItem("小翠","输液"));
//        m_modelOverQueue->Add(CommonModelItem("张三","输液" ));
//        m_modelOverQueue->Add(CommonModelItem("小翠","输液"));
//    }
//    else if(1 == page){
//        m_modelOverQueue->Add(CommonModelItem("张大大","过号" ));
//        m_modelOverQueue->Add(CommonModelItem("王笑笑","过号"));
//    }

    m_modelOverQueue->EndAdd();
    emit dataLoadComplate(OverQueue, 0);
    qDebug() << "TransfuseController::RunUpdateOverQueueModel";
}


// [线程]在线程中更新《滴速检测》队列
// ***在这里要完成到服务器的数据请求
void TransfuseController::RunUpdateDropSpeedTestQueueModel(int page)
{
    // 构建需要请求的数据
    QVector<int>    reqID;
    QVector<int>    eraseID;
    int             tLast = time(NULL) - 300;

    m_monitorLock.lock();
    QMap<int, TransfuseMonitorData>::iterator item;
    for(item = m_monitorData.begin(); item != m_monitorData.end(); item++)
    {
        if(item->time < tLast)
        {
            eraseID.push_back(item.key());
        }
        else if(item->name == "")
        {
            reqID.push_back(item.key());
        }
    }

    // 删除过期项
    for(int i = 0; i < eraseID.count(); i++)
    {
        m_monitorData.remove(eraseID.at(i));
    }

    int cnt = m_monitorData.count();
    if(0 == cnt || page > (cnt / 22))
    {
        m_monitorLock.unlock();
        emit dataLoadComplate(DropSpeed, -1);
        return; // 没有需要的数据
    }

    m_monitorLock.unlock();
    // 到服务器请求患者姓名
    // ***
    qDebug() << "add data";
    QThread::sleep(1);
    // 显示数据
    m_monitorLock.lock();
    int k = 0;
    m_modeldropSpeedTestQueue->BeginAdd();
    for(item = m_monitorData.begin() + (page * 22);
        item != m_monitorData.end() && k < 22;
        item++, k++)
    {
        if("" != item->name)
        {
            m_modeldropSpeedTestQueue->Add(
                        CommonModelItem(item->uid, item->name,
                                        QString("%1滴/min").arg(item->speed)));
        }
        else
        {
            m_modeldropSpeedTestQueue->Add(
                        CommonModelItem(QString("设备[%1]").arg(item.key()), "",
                                        QString("%1滴/min").arg(item->speed)));
        }
    }

    m_modeldropSpeedTestQueue->EndAdd();
    m_monitorLock.unlock();
    emit dataLoadComplate(DropSpeed, 0);
}
