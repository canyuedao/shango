#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qxmlrpccall.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // QXmlRpcCall call("192.168.0.222", 8069, "BSZYY_0505");
    QXmlRpcCall call("127.0.0.1", 8000, "BSZYY_0505");

    if(false == call.Login("admin", "shangoadmin", "11" ))
    {
        qDebug() << "error: " << call.Error();
    }

    QString request = "{\n"
            "\"funcid\":\"600004\",\n"
            "\"sender\":\"22\",\n"
            "\"data\": {\"dispose_record_of_queue_id\": 4},\n"
            "\"tag\": 0,\n"
            "\"timestamp\": 0.02,\n"
            "\"rescode\": 0,\n"
            "\"resdesc\": 0\n"
            "}";
    QString response;

    if(false == call.Execute(request, response))
    {
        qDebug() << "error: " << call.Error();
    }
    else
    {
        qDebug() << "recv: " << response;
    }
//    QXmlRpcCreator xml("login");
//    QDateTime dt = QDateTime::currentDateTime();

//    xml.PushInt(4);
//    xml.PushString("这里是说明");
//    xml.PushBoolean(true);
//    xml.PushDateTime(dt);
//    xml.PushDouble(1.632);
//    xml.PushNil();

//    xml.Clear();

//    QString json = "{\n"
//            "\"funcid\":\"600004\",\n"
//            "\"sender\":\"22\",\n"
//            "\"data\": {\"dispose_record_of_queue_id\": 4},\n"
//            "\"tag\": 0,\n"
//            "\"timestamp\": 0.02,\n"
//            "\"rescode\": 0,\n"
//            "\"resdesc\": 0\n"
//            "}";
//    xml.PushStruct(json);


//    QString str = xml.Dump();
//    qDebug("%s", str.toUtf8().data());


//    QXmlRpcParser parser;
//    QString xml = "<?xml version='1.0'?>\n"
//            "<methodResponse>\n"
//            "<params>\n"
//            "<param>\n"
//            "<value><string>{\"rescode\": 1, \"timestamp\": \"08:24:34\", \n"
//            "\"resdesc\": null, \"tag\": 0, \"data\": [{\"order_line\": [], \"partner_id\": 513, \n"
//            "\"id\": 10, \"enqueue_datetime\": \"2015-05-08 16:58:56\", \"visit_no\": \n"
//            "\"2015031900002\", \"employee_id\": 0, \"attendance_card\": \"\", \"state\": \n"
//            "-1, \"room_id\": 0, \"registered_id\": 0, \"dispose_id\": 0, \"department_id\": \n"
//            "25, \"business\": \"\u6253\u9488\", \"is_affirm\": \"0\", \"order_id\": \n"
//            "0, \"spell\": \"021401\", \"hospital_number\": \"\", \"medicare_card\": \"\", \n"
//            "\"internal_code\": \"10000000100\", \"name\": \"021401\", \"identity_card\":\n"
//            "\"\", \"patient_id\": 100, \"visit_date\": \"2015-05-08\", \"patient_code\": \n"
//            "\"2015031900002\"}], \"funcid\": \"600002\"}</string></value>\n"
//            "</param>\n"
//            "</params>\n"
//            "</methodResponse>";

//    if( parser.ParseXML(xml) )
//    {
//        qDebug() << parser.GetResult().at(0).toString();
//    }

    return app.exec();
}
