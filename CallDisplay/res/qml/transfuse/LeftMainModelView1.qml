/************************************
** 视窗左边综合信息列表的每一列显示层
** 包括病人姓名、当前排队位置和状态
*************************************/

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

/* list cell */
Rectangle {
    property int textSize: 32
    property color textColor: "#400000"

    anchors.fill: parent;
    color:  "transparent";

//    // header 标题栏
//    Image {
//        id: wrapper;
//        width: parent.width;
//        height: parent.height/12;
//        source: "../../image/leftTitleBottom.png"

//        Image {
//            width: parent.width-16;
//            height: parent.height-10;
//            anchors { top: parent.top; left: parent.left; topMargin: 5; leftMargin: 8;}
//            source: "../../image/leftTitle.png"

//            Text {text: "综合集中信息屏"; color: "white";font.family: "FZLanTingHei-B-GBK"; font.pointSize: textSize; font.bold: true; anchors.top: parent.top; anchors.topMargin:15; anchors.horizontalCenter: parent.horizontalCenter; }
//        }
//    }

    Rectangle {
        width: parent.width;
        height: parent.height-parent.height/12;
        anchors.top:parent.top;
        color:  "transparent";

        Image {
            id: img;
            width: parent.width*0.4;
            height: parent.height*0.8;
            anchors{ top:parent.top; topMargin:parent.height*0.2; left:parent.left; leftMargin: parent.width*0.05;}
            source: "../../image/doctor1.png"

            Text {text: "谢晓峰（副主任医生）"; color: "black";font.family: "FZLanTingHei-B-GBK"; font.pointSize: textSize; font.bold: true; anchors.bottom: parent.bottom; anchors.bottomMargin:15; anchors.horizontalCenter: parent.horizontalCenter; }
        }

        Image {
            anchors{ top:parent.top; topMargin:parent.height*0.5; left:img.right; leftMargin: parent.width*0.05;}
            source: "../../image/pp.png"
        }

//           /* 显示 patient name */
//             Text {
//                id: idName
//                font.pointSize: textSize
//                color: textColor
//                font.family: "FZLanTingHei-B-GBK"
//                horizontalAlignment: Text.AlignHCenter;
//                Layout.preferredWidth: parent.width/3;
//            }

//            /* 显示病人当前状态 status */
//            Text {
//                id: idStatus
//                font.pointSize: textSize
//                color: textColor
//                font.family: "FZLanTingHei-B-GBK"
//                horizontalAlignment: Text.AlignHCenter;
//                Layout.preferredWidth: parent.width/3;
//            }

    }
}
