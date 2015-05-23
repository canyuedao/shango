/*
 * 在这里定义全局变量
 */
#include "globalobject.h"

GlobalObject::GlobalObject(QObject *parent) : QObject(parent)
{
    str = "根据卫生部8月5日通知和卫生局的工作部署，璧山医院。。。";
}

GlobalObject::~GlobalObject()
{

}

// 单例模式
GlobalObject* GlobalObject::getInstance()
{
    static GlobalObject* ins = NULL;

    if(NULL == ins)
    {
        ins = new GlobalObject;
    }

    return ins;
}

// 获取轮询时间
int GlobalObject::switchinterval()
{
    return 1000 * 5;
}


QString GlobalObject::bottomTitleString(){

    return str;
}
