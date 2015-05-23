#ifndef TRANSFUSECONTROLLER_H
#define TRANSFUSECONTROLLER_H

#include <QObject>
#include <QFuture>
#include <QMap>
#include <QMutex>
#include "../other/heart.h"

struct TransfuseMonitorData
{
    QString     uid;
    QString     name;
    int         speed;
    int         time;
};


class CommonModel;
class TransfuseController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject *modelInfusionQueue      READ modelInfusionQueue         NOTIFY modelQueueChanged)
    Q_PROPERTY(QObject *modelDoctorQueue        READ modelDoctorQueue           NOTIFY modelQueueChanged)
    Q_PROPERTY(QObject *modelNowSeeDoctorQueue  READ modelNowSeeDoctorQueue     NOTIFY modelQueueChanged)
    Q_PROPERTY(QObject *modelOverQueue          READ modelOverQueue             NOTIFY modelQueueChanged)
    Q_PROPERTY(QObject *modelDropSpeedTestQueue READ modelDropSpeedTestQueue    NOTIFY modelQueueChanged)

    enum ModelType {Queue = 0, Doctor = 1,
                    NowSee = 2, OverQueue = 3, DropSpeed = 4};
public:
    explicit TransfuseController(QObject *parent = 0);
    ~TransfuseController();

signals:
    void modelQueueChanged();
    void dataLoadComplate(int type, int err);
    /* 弹出窗信息的信号 */
    void popViewInformation(const QString &doctorPhoto,
                            const QString &doctorInfor,
                            const QString &popState,
                            const QString &patientName,
                            const QString &seeDoctorSite);

/* 初始化 */
private:
    void InitModel();

public slots:
    void upInfusionQueueModel(int page);              // 更新输液信息
    void upDoctorQueueModel(int page);                // 更新医生信息
    void upNowSeeDoctorQueueModel(int page);          // 更新当前就诊信息
    void upOverQueueModel(int page);                  // 更新过号信息
    void upDropSpeedTestQueueModel(int page);         // 更新输液滴速检测信息
    void onMonitorRecv(int id, int sp);

public:
    QObject* modelInfusionQueue();                    // 获取输液排队模型
    QObject* modelDoctorQueue();                      // 获取医生信息模型
    QObject* modelNowSeeDoctorQueue();                // 获取当前就诊模型
    QObject* modelOverQueue();                        // 获取过号模型
    QObject* modelDropSpeedTestQueue();               // 获取输液滴速检测模型

private:
    void RunUpdateInfusionQueueModel(int page);       // 请求并加载输液排队数据
    void RunUpdateDoctorQueueModel(int page);         // 请求并加载医生信息数据
    void RunUpdateNowSeeDoctorQueueModel(int page);   // 请求并加载当前就诊数据
    void RunUpdateOverQueueModel(int page);           // 请求并加载过号数据
    void RunUpdateDropSpeedTestQueueModel(int page);  // 请求并加载输液滴速检测数据

private:
    CommonModel              *m_modelInfusionQueue;         // 输液
    CommonModel              *m_modelDoctorQueue;           // 医生
    CommonModel              *m_modelNowSeeDoctorQueue;     // 当前就诊
    CommonModel              *m_modelOverQueue;             // 过号
    CommonModel              *m_modeldropSpeedTestQueue;    // 滴速检测

    QFuture<void>            m_futureInfusionQueue;
    QFuture<void>            m_futureDoctorQueue;
    QFuture<void>            m_futureNowSeeDoctorQueue;
    QFuture<void>            m_futureOverQueue;
    QFuture<void>            m_futureDropSpeedTestQueue;


    Heart                    m_heart;      // 监测心跳
    QMap<int, TransfuseMonitorData>     m_monitorData;
    QMutex                              m_monitorLock;
};

#endif // TRANSFUSECONTROLLER_H
