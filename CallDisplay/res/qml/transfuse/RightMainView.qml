/************************************
** 视窗右边展示基层
** 加载右边标题栏、当前就诊框和过号信息框
*************************************/

import QtQuick 2.3


Rectangle{
    anchors.fill: parent;
    color: "#5C401E";

    /* 标题栏 */
    Image {
        id: rightTitle1
        width: parent.width-20;
        height: parent.height/8;
        anchors {top: parent.top; topMargin: 8; right: parent.right; rightMargin: 10}
        source: "../../image/rightTitle1.png"
    }

    /* 加载right model展示层的Loader */
    Loader {
        id: right_list2;
        width: parent.width-20;
        height: parent.height/2-28;
        anchors {top: rightTitle1.bottom; topMargin: 6; right: parent.right; rightMargin: 10}
        source: "RightModelView.qml";
    }

    /* 加载right bottom展示层的Loader */
    Loader {
        id: right_list3;
        width: parent.width-20;
        height: parent.height*3/8;
        anchors {bottom: parent.bottom; bottomMargin: 6; right: parent.right; rightMargin: 10}
        source: "RightBottomView.qml";
    }
}
