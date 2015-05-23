/************************************
** 视窗右边中间展示层
** 显示当前就诊病人信息
*************************************/

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Image{
    id: rRect;
    anchors.fill: parent;
    source: "../../image/rightModel.png"

    property int titleSize: 28;         // 定义标题字体大小
    property int contentSize: 32;       // 定义内容字体大小

    /* 标题栏 */
    Component {
        id: rList_Header1;
        Image {
            width: parent.width;
            height: rRect.height/7;
            source: "../../image/rightTitle2.png"

            Text {
                text: "当前就诊";
                color: "red";
                font.family: "FZLanTingHei-B-GBK";
                font.pointSize: titleSize;
                anchors.fill: parent;
                horizontalAlignment: Text.AlignHCenter;         // 左右居中
                verticalAlignment:Text.AlignVCenter;            // 上下居中
            }
        }
    }

    /* 内容列 */
    Component {
        id: rList_Model1;
        Item {
            id: model_wrapper;
            width: parent.width;
            height: rRect.height/7;

            RowLayout {
                anchors.fill: parent;
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                spacing: 0;
                Text {
                    text: userName;
                    color: "white";
                    font.family: "FZLanTingHei-B-GBK";
                    font.pointSize: contentSize;
                    horizontalAlignment: Text.AlignHCenter;          // 左右居中
                    verticalAlignment:Text.AlignVCenter;             // 上下居中
                    Layout.preferredWidth: parent.width/2;
                }

                Text {
                    text: do_thing;
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

    ListView {
        id: rListView;
        width: parent.width;
        height: parent.height;
        anchors.top: parent.top;
        interactive: false // 禁止交互
        spacing: 10;

        delegate: rList_Model1;                         // 内容模版定义
        header: rList_Header1;                          // 作为标题
        model: transfuseController.modelNowSeeDoctorQueue;      // 数据列表
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
            transfuseController.upNowSeeDoctorQueueModel(page++)
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
