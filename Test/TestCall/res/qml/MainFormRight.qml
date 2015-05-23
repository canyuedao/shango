import QtQuick 2.0

Rectangle {
    anchors {
        right: parent.right
        top: parent.top;
        bottom: parent.bottom
    }
    color: "transparent"

    Text {
        id: idTtitle;
        anchors.horizontalCenter: parent.horizontalCenter
        text: "皮试呼叫"
        font.pixelSize: 24
        color: "white"
        font.family: "FZLanTingHei-B-GBK"
    }

    Rectangle {
        id: idSpace
        color: "black"
        height: 2
        anchors.top: idTtitle.bottom
        anchors.right: parent.right
        anchors.left: parent.left
    }

    Rectangle {
        anchors.top: idSpace.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10

        /* 呼叫显示 */
        Column {
            spacing: 10
            anchors.left: parent.left
            anchors.right: parent.right

            MainFormCallRow {
                callId: "0001"
                name: "呼叫用户"
                status: "正在呼叫"
            }

            Column {
                id: idUsers
                spacing: 10
                anchors.left: parent.left
                anchors.right: parent.right

                Component {
                    id: idUserComponent
                    MainFormRow {

                    }
                }
            }
        }
    }

    Rectangle {
        color: "black"
        width: 1
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom;
    }

    Component.onCompleted: {
        addUser("0002", "用户11", "等待输液");
        addUser("0003", "用户12", "等待输液");
        addUser("0004", "用户13", "等待输液");
        addUser("0005", "用户14", "等待输液");
        addUser("0006", "用户15", "等待输液");
    }

    /* 添加用户 */
    function addUser(id, name, status) {
        var obj = idUserComponent.createObject(idUsers)
        obj.callId = id;
        obj.name = name;
        obj.status = status
    }
}

