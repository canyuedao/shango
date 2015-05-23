/************************************
** 视窗底部字幕显示层
** 包括时间和滚动字幕
*************************************/

import QtQuick 2.3


Rectangle{
    anchors.fill: parent;
    id: screen;

    property color textColor: "white";
    property int textSize: 28

    color: "#180F05"

    /* 得到本地时间 */
    function showTime() {
        var dt = new Date()
        var str = dt.toLocaleString(Qt.locale(), "hh:mm");

        timeshow.text = str;
    }

    Rectangle {
        width: parent.width/15;
        height: parent.height;
        anchors { left: parent.left; top: parent.top; bottom: parent.bottom;}
        color: "#340C0C";
        z:1;
        Text {
            id: timeshow;
            color: "white"
            anchors{fill: parent; top: parent.top; bottom: parent.bottom;}
            font.family: "FZLanTingHei-B-GBK"// "方正兰亭粗黑_GBK"
            font.pointSize: textSize
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment:Text.AlignVCenter;
        }

        Component.onCompleted: {
            showTime();
        }

        /* 定时显示时间屏 */
        Timer {
            repeat: true
            running: true
            onTriggered: {
                showTime();
            }
        }
    }

    /* 滚动字幕显示 */
    Row {
        height: parent.height;
        z:0;
        NumberAnimation on x { from: screen.width; to: -text.width; duration: 6000+text.width*20; loops: Animation.Infinite }
        Text {
            id: text;
            anchors{top: parent.top; bottom: parent.bottom;}
            font.family: "FZLanTingHei-B-GBK";
            font.pointSize: textSize;
            color: screen.textColor;
            text: cpp.bottomTitleString
            verticalAlignment:Text.AlignVCenter;
        }
    }
}
