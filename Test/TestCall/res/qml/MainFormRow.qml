import QtQuick 2.0

Rectangle {
    property alias callId: idCallID.text
    property alias name: idName.text
    property alias status: idStatus.text
    property color textColor: "white"

    height: 48
    anchors.left: parent.left
    anchors.right: parent.right
    color: "transparent"

    /* ID */
    Text {
        id: idCallID
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 24
        color: textColor
        font.family: "FZLanTingHei-B-GBK"
    }

    /* name */
    Text {
        id: idName
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 24
        color: textColor
        font.family: "FZLanTingHei-B-GBK"
    }

    /* status */
    Text {
        id: idStatus
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        font.pixelSize: 24
        color: textColor
        font.family: "FZLanTingHei-B-GBK"
    }
}

