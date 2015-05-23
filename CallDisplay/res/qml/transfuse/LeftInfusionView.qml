/************************************
** 视窗左边综合信息展示页
** 展示已挂号病人当前信息
*************************************/

import QtQuick 2.3

Rectangle {
    id: left_viewer;
    anchors.fill: parent;

//    property var obj: list();
    property int person_index: 0;   // 记录信息表中人数
    property int textSize: 32;

    // header 标题栏
    Image {
        id: wrapper;
        width: parent.width;
        height: left_viewer.height/12;
        source: "../../image/leftTitleBottom.png"

        Image {
            width: parent.width-16;
            height: parent.height-10;
            anchors { top: parent.top; left: parent.left; topMargin: 5; leftMargin: 8;}
            source: "../../image/leftTitle.png"

            Text {text: "综合集中信息屏"; color: "white";font.family: "FZLanTingHei-B-GBK"; font.pointSize: textSize; font.bold: true; anchors.top: parent.top; anchors.topMargin:15; anchors.horizontalCenter: parent.horizontalCenter; }
        }
    }

    /* Content View*/
    CallQueue {
        anchors.top:wrapper.bottom;
    }
}




