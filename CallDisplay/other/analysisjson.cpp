#include "analysisjson.h"
#include <QHostInfo>
AnalysisJson::AnalysisJson(QObject *parent) : QObject(parent)
{

}

AnalysisJson::~AnalysisJson()
{

}

/* 获取jsonObject对象 */
QJsonObject AnalysisJson::getJsonObject(QByteArray data){
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(data, &err);
    if(err.error != QJsonParseError:: NoError){
        if(!(json.isEmpty() || json.isNull())){
            QJsonObject jsonObect = json.object();
            return jsonObect;
        }
    }
}

/* 获取消息队列 */
QJsonArray AnalysisJson::getMsgArrayByKey(QString key, QJsonObject obj){
    QJsonObject::const_iterator it = obj.find("msg");
    QJsonArray msgArray = it.value().toArray();
    return msgArray;

}


void AnalysisJson::manageJson(QByteArray data){


}

QString AnalysisJson::genRequestJson(int funcid){
    QString localIp;
    QString localhostName=QHostInfo::localHostName();
    QHostInfo info=QHostInfo::fromName(localhostName);
    foreach(QHostAddress address,info.addresses())
    {
      if(address.protocol()==QAbstractSocket::IPv4Protocol){
        //qDebug()<<address.toString(); //输出IPV4的地址
        localIp = address.toString();
      }
    }
    QuickJson infusObj;
    infusObj.ValueSet("version",1.0);
    infusObj.ValueSet("contentype","");
    infusObj.ValueSet("sender",localIp);
    infusObj.ArrayAdd("receiver","");
    infusObj.ValueSet("timestamp",0);
    infusObj.ValueSet("live",0);
    infusObj.ValueSet("data.funcid",funcid);
    infusObj.ValueSet("data.rescode",0);
    infusObj.ValueSet("data.resdesc",0);

    infusObj.ArrayAdd("data.msg.state",1);
    infusObj.ValueSet("data.msg.current_page",1);
    infusObj.ValueSet("data.msg.pate_size",22);
    infusObj.ValueSet("data.msg.sub_number","订阅号");

    //infusObj.ArrayAdd("data.msg",msgObj.toJson());
    infusObj.ValueSet("digest",0);
    infusObj.ValueSet("signature",0);
    return infusObj.toJson();
}
