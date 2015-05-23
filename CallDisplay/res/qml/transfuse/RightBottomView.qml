/************************************
** 视窗右边底部过号展示层
** 显示过号病人的信息
*************************************/

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Image{
    id: rRect2;
    anchors.fill: parent;
    source: "../../image/rightBottom.png"

    property int titleSize: 28;         // 定义标题字体大小
    property int contentSize: 32;       // 定义内容字体大小

    /* 过号标题栏 */
    Component {
        id: rList_Header2;
        Image {
            width: parent.width;
            height: rRect2.height/5;
            source: "../../image/rightTitle2.png"

            Text {
                text: "过号信息";
                color: "#EEAD0E";
                font.family: "FZLanTingHei-B-GBK";
                font.pointSize: titleSize;
                anchors.fill: parent;
                horizontalAlignment: Text.AlignHCenter;         // 左右居中
                verticalAlignment:Text.AlignVCenter;            // 上下居中
            }
        }
    }

    /* 过号内容列表内容模版 */
    Component {
        id: rList_Model2;
        Item {
            id: model_wrapper2;
            width: parent.width;
            height: rRect2.height/6;

            RowLayout {
                anchors.fill: parent;
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                spacing: 0;

                /* 过号者姓名 */
                Text {
                    text: patientName;
                    color: "white";
                    font.family: "FZLanTingHei-B-GBK";
                    font.pointSize: contentSize;
                    horizontalAlignment: Text.AlignHCenter;         // 左右居中
                    verticalAlignment:Text.AlignVCenter;            // 上下居中
                    Layout.preferredWidth: parent.width/2;
                }

                /* 过号者应做事的名称 */
                Text {
                    text: over_thing;
                    color: "white";
                    font.family: "FZLanTingHei-B-GBK";
                    font.pointSize: contentSize;
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment:Text.AlignVCenter;
                    Layout.preferredWidth: parent.width/2;
                }
            }
        }
    }

    /* 列表显示 */
    ListView {
        id: rListView2;
        width: parent.width;
        height: parent.height;
        anchors.top: parent.top;
        interactive: false // 禁止交互
        spacing: 10;

        delegate: rList_Model2;                          // 内容模版定义
        header: rList_Header2;                           // 作为标题
        model: transfuseController.modelOverQueue;       // 数据列表
    }

    // 定时刷新数据
    Timer {
        id: timer;
        property int page: 0
        interval:cpp.switchinterval
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            // 定时刷新数据
            transfuseController.upOverQueueModel(page++)
        }
    }

    Component.onCompleted: {
        transfuseController.dataLoadComplate.connect(onErr)
    }

    function onErr(tp, err) {
        if(3 == tp && 0 != err) {
            console.debug("transfuseController.OverQueue end");
            timer.page = 1;
            transfuseController.upOverQueueModel(0);
        }
    }
}
