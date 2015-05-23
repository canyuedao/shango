#ifndef QUICKJSON_H
#define QUICKJSON_H
#include <QJsonDocument>
#include <QString>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

class QStringList;
class QuickJson
{
public:
    QuickJson();
    ~QuickJson();

public:
    bool        Parse(QString json);
    QString     toJson();
    void        Reset();

    bool        ValueSet(QString keyPath, const QJsonValue& val);
    bool        ArrayAdd(QString keyPath, const QJsonValue& val);

    QJsonValue  ValueGet(QString keyPath);

private:
    bool        InnerValueSet(const QStringList& keys, int dep,
                         QJsonObject &obj, const QJsonValue& val,
                              bool isArray = false);
    QJsonValue   InnerValueGet(const QStringList& keys, int dep,
                                  const QJsonObject &obj);

private:
    QJsonDocument   m_doc;
    QString         m_error;
};

#endif // QUICKJSON_H
