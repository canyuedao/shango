import QtQuick 2.3
import Shango 1.0

Rectangle {
    property alias mouseArea: mouseArea

    width: 360
    height: 360

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Text {
        id: txt;
        anchors.centerIn: parent
        text: "RabbitMQ client"
    }


    RabbitMQTest {
        onConnected: {
            txt.color = "green";
        }

        onClosed: {
            txt.color = "red";
        }

        onMessage: {
            txt.text = txt.text + "\r\n" + msg;
        }

        onError: {
            txt.text = err;
            txt.color = "red";
        }
    }
}
