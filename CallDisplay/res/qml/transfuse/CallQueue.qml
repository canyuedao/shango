import QtQuick 2.0

Rectangle {
    id: callQueue
    width: parent.width
    height: parent.height-parent.height/12

    // 格子背景
    Flow {
        z: 0
        anchors.fill: parent
        spacing: 0

        Repeater {
            model: 22

            Rectangle {
                color: "#F8F8F8"
                width: callQueue.width / 2 - 1
                height: 84

                Rectangle {
                    anchors.fill: parent
                    anchors.leftMargin: ((index % 2) == 0) ? 0 : 1
                    anchors.rightMargin: ((index % 2) == 0) ? 1 : 0
                    color: ((Math.floor(index / 2) % 2) == 0)?"#ffffff":"#FFD8A9"
                }
            }
        }
    }


    // 数据显示
    GridView {
        z: 1
        width: parent.width
        height: parent.height
        interactive: false // 禁止交互
        cellWidth: 717
        cellHeight: 84
        model: transfuseController.modelInfusionQueue
        delegate: Rectangle {
            color: "transparent"
            width: callQueue.width / 2 - 1
            height: 84

            /* 显示病人排队位数 */
            Text {
                text: sid
                font.pointSize: 32
                color: "#422b10"
                font.family: "FZLanTingHei-B-GBK"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 60
            }

            /* 显示 patient name */
            Text {
                text: name
                font.pointSize: 32
                color: "#422b10"
                font.family: "FZLanTingHei-B-GBK"
                anchors.centerIn: parent
            }

            /* 显示病人当前状态 status */
            Text {
                text: status
                font.pointSize: 32
                color: "#422b10"
                font.family: "FZLanTingHei-B-GBK"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 60
            }
        }
    }

    // 定时刷新数据
    Timer {
        id: viewTimer;
        property int page: 0
        interval: cpp.switchinterval
        running: true
        repeat: true
        triggeredOnStart: true
        onTriggered: {
            // 定时刷新数据
            transfuseController.upInfusionQueueModel(page++)
        }
    }

    Component.onCompleted: {
        transfuseController.dataLoadComplate.connect(onErr)
    }

    function onErr(tp, err) {
        if(0 == tp && 0 != err) {
            console.debug("[CallQueue] Queue end: ", tp, "/", err);
            viewTimer.stop();
        }
    }
}

