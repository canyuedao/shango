#ifndef ANALYSISJSON_H
#define ANALYSISJSON_H

#include <QObject>
#include <QByteArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include "../other/quickjson.h"
class AnalysisJson : public QObject
{
    Q_OBJECT
public:
    explicit AnalysisJson(QObject *parent = 0);
    ~AnalysisJson();

public:
    QString genRequestJson(int);
private:
    QJsonObject getJsonObject(QByteArray data);
    QJsonArray getMsgArrayByKey(QString key, QJsonObject obj);

signals:

public slots:
    void manageJson(QByteArray data);


};

#endif // ANALYSISJSON_H
