/*
 * 显示屏启动画面(Loading)
 * 当设备启动时显示的画面
 */
import QtQuick 2.0

Rectangle {
    width: 360
    height: 280
    color: "transparent"

    Column {
        anchors.centerIn: parent
        spacing: 20

        /* 占位元素 */
        Rectangle {
            width: 100
            height: 100
            color: "transparent"
        }

        /* 显示文本 */
        Text {
            text: "正在连接服务器..."
            font.pixelSize: 48
            color: "#ffffff"
            font.family: "FZLanTingHei-B-GBK"
        }

        /*  启动动化 */
        AnimatedImage {
            anchors.horizontalCenter: parent.horizontalCenter
            source: "../image/loading.gif"
        }
    }
}

