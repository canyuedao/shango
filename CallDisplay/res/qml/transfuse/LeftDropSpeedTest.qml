import QtQuick 2.0

Rectangle {
    id: dropView
    anchors.fill: parent;

    property int textSize: 32;

    // header 标题栏
    Image {
        id: wrapper;
        width: parent.width;
        height: dropView.height/12;
        source: "../../image/leftTitleBottom.png"

        Image {
            width: parent.width-16;
            height: parent.height-10;
            anchors { top: parent.top; left: parent.left; topMargin: 5; leftMargin: 8;}
            source: "../../image/leftTitle.png"

            Text {text: "综合集中滴液检测信息屏"; color: "white";font.family: "FZLanTingHei-B-GBK"; font.pointSize: textSize; font.bold: true; anchors.top: parent.top; anchors.topMargin:15; anchors.horizontalCenter: parent.horizontalCenter; }
        }
    }

    Rectangle {
        id: dropTest
        width: parent.width
        height: parent.height-parent.height/12
        anchors.top:wrapper.bottom;

        // 格子背景
        Flow {
            z: 0
            anchors.fill: parent
            spacing: 0

            Repeater {
                model: 22

                Rectangle {
                    color: "#F8F8F8"
                    width: dropTest.width / 2 - 1
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
            cellWidth: dropTest.width / 2 - 1
            cellHeight: 84
            model: transfuseController.modelDropSpeedTestQueue
            delegate: Rectangle {
                color: "transparent"
                width: dropTest.width / 2 - 1
                height: 84

                /* 显示病人号数 */
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

                /* 显示输液滴速 */
                Text {
                    text: dropStatus
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
            repeat: true
            running: true
            triggeredOnStart: true
            onTriggered: {
                // 定时刷新数据
                transfuseController.upDropSpeedTestQueueModel(page++)
            }
        }
    }

    Component.onCompleted: {
        transfuseController.dataLoadComplate.connect(onErr)
    }

    function onErr(tp, err) {
        if(4 == tp && 0 != err) {
            console.debug("transfuseController.DropSpeed end");
            viewTimer.stop();
        }
    }
}

