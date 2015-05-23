#include "quickjson.h"
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>


QuickJson::QuickJson()
{

}

QuickJson::~QuickJson()
{

}

// 解析json
bool QuickJson::Parse(QString json)
{
    QJsonParseError     err;
    QJsonDocument       doc;

    doc = QJsonDocument::fromJson(json.toUtf8(), &err);
    if(QJsonParseError::NoError != err.error)
    {
        m_error = err.errorString();
        return false;
    }

    if(false == doc.isObject())
    {
        m_error = "not object";
        return false;
    }

    m_doc = doc;
    return true;
}

// 转换为json
QString QuickJson::toJson()
{
    return m_doc.toJson();
}

// 重置
void QuickJson::Reset()
{
    m_doc.setObject(QJsonObject());
}

// 设置值
bool QuickJson::ValueSet(QString keyPath, const QJsonValue& val)
{
    QStringList paths = keyPath.split('.');
    QJsonObject root = m_doc.object();

    if(false == InnerValueSet(paths, 0, root, val, false))
    {
        return false;
    }

    m_doc.setObject(root);
    return true;
}

// 数组添加值
bool QuickJson::ArrayAdd(QString keyPath, const QJsonValue &val)
{
    QStringList paths = keyPath.split('.');
    QJsonObject root = m_doc.object();

    if(false == InnerValueSet(paths, 0, root, val, true))
    {
        return false;
    }

    m_doc.setObject(root);
    return true;
}

// 取值
QJsonValue QuickJson::ValueGet(QString keyPath)
{
    QStringList paths = keyPath.split('.');
    QJsonObject root = m_doc.object();

    return InnerValueGet(paths, 0, root);
}

// 添加值
bool QuickJson::InnerValueSet(const QStringList &keys, int dep,
                              QJsonObject& obj, const QJsonValue &val,
                              bool isArray)
{
    // 查找父对像
    if(dep < (keys.count() - 1))
    {
        QJsonObject::iterator   item;
        QJsonObject             keyObj;
        QString                 key;

        key = keys.value(dep);
        item = obj.find(key);
        if(obj.end() != item)
        {
            if(false == item.value().isObject())
            {
                return false;
            }

            keyObj = item.value().toObject();
        }

        if(false == InnerValueSet(keys, dep + 1, keyObj, val, isArray))
        {
            return false;
        }

        obj.insert(key, keyObj);
        return true;
    }
    else if(dep != (keys.count() - 1))
    {
        return false;
    }

    // 插入
    QString                 key;

    key = keys.value(dep);
    if(false == isArray)
    {
        // 添加新值
        obj.insert(key, val);
    }
    else
    {
        // 添加数组
        QJsonObject::iterator   item;
        QJsonArray              arr;

        item = obj.find(key);
        if(obj.end() != item)
        {
            if(false == item.value().isArray())
            {
                return false;
            }

            arr = item.value().toArray();
        }

        arr.append(val);
        obj.insert(key, arr);
    }


    return true;
}

// 获取值
QJsonValue QuickJson::InnerValueGet(const QStringList &keys,
                                    int dep, const QJsonObject &obj)
{
    if(dep < (keys.count() - 1))
    {
        QString key = keys.value(dep);
        if(false == obj.contains(key)
                || false == obj[key].isObject())
        {
            return QJsonValue();
        }

        return InnerValueGet(keys, dep + 1, obj[key].toObject());
    }
    else if(dep != (keys.count() - 1))
    {
        return QJsonValue();
    }

    // 返回值
    QString key = keys.value(dep);
    if(obj.contains(key))
    {
        return obj[key];
    }

    return QJsonValue();
}


