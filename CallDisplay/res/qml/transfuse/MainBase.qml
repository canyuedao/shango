/************************************
** 主窗口
*************************************/

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQml 2.2

Rectangle{
    anchors.fill: parent;
    color: "#FFD39B";
    property var leftBody: left_list
    property var leftBodyTmp: left_list_tmp
    property bool leftBodySwitch: false

    // 窗口左边视窗的基层
    Rectangle {
        width: parent.width*3/4;
        height: parent.height-parent.height/15;
        Rectangle {
            z:0;
            width: parent.width;
            height: parent.height;

            Loader {
                id: left_list;
                anchors.fill: parent
                source: "LeftInfusionView.qml"
            }

            Loader {
                id: left_list_tmp;
                visible: false
                anchors.fill: parent
                source: ""
            }
        }

        /* 呼叫弹出窗 */
        Loader {
            id: popRect;
            z:1;
            width: parent.width;
            height: parent.height-parent.height/12;
            anchors.bottom: parent.bottom;
            source: "LeftPopView.qml";
        }
    }

    // 窗口右边视窗的基层
    Rectangle {
        width: parent.width*1/4;
        height: parent.height-parent.height/15;
        anchors.leftMargin: 5;
        anchors.right: parent.right;
        Loader {
            id: right_list;
            width: parent.width;
            height: parent.height;
            source: "RightMainView.qml"
        }
    }

    // 窗口底部字幕的基层
    Rectangle {
        width: parent.width;
        height: parent.height/15;
        anchors.bottom: parent.bottom;
        color: "#E0FFFF";
        Loader {
            id: bottom_View;
            width: parent.width;
            height: parent.height;
            source: "BottomView.qml"
        }
    }

    Component.onCompleted: {
        transfuseController.dataLoadComplate.connect(changePage)
    }

    // 改变显示信息页
    function changePage(tp, err) {
        if(0 == err && false != leftBodySwitch
                && (0 == tp || 1 == tp || 4 == tp)) {
            leftBodySwitch = false;
            // 交互显示
            if(false == leftBodyTmp.visible) {
                var obj = leftBodyTmp;
                // switch
                leftBodyTmp = leftBody;
                leftBody = obj;
                // show
                leftBodyTmp.visible = false;
                leftBody.visible = true;
                // hide
                leftBodyTmp.source = "";
            }

            return;
        } else if(-1 == err) { // err == -1
            switch(tp) {
            case 0:
                leftBodyTmp.source = "LeftDoctorView.qml";
                leftBodySwitch = true;
                break;
            case 1:
                leftBodyTmp.source = "LeftDropSpeedTest.qml";
                leftBodySwitch = true;
                break;
            case 4:
                leftBodyTmp.source = "LeftInfusionView.qml";
                leftBodySwitch = true;
                break;
            }
        }
    }

//    Timer {
//        id:timer
//        interval: 10000;
//        repeat: true;
//        running: true;
//        onTriggered: changePage();
//    }

}
