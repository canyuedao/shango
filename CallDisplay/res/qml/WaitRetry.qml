import QtQuick 2.0

Rectangle {
    width: 100
    height: 62
    color: "transparent"

    Row {
        anchors.centerIn: parent

        Text {
            text: "连接服务器失败，等待"
            font.pixelSize: 48
            color: "#ffffff"
            font.family: "FZLanTingHei-B-GBK"
        }

        Text {
            id: txtSeconds
            text: "10"
            font.pixelSize: 48
            color: "#ff0000"
            font.family: "FZLanTingHei-B-GBK"
        }

        Text {
            text: "秒重试"
            font.pixelSize: 48
            color: "#ffffff"
            font.family: "FZLanTingHei-B-GBK"
        }
    }

    Timer {
        property int time: 10
        running: true
        interval: 1000
        repeat: true
        onTriggered: {
            time--;
            if(time <= 0) {
                retryConnect();
            }

            txtSeconds.text = time;
        }
    }
}

