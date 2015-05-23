import QtQuick 2.0

Rectangle {
    height: 69
    anchors {
        left: parent.left
        right: parent.right
        bottom: parent.bottom
    }
    color: "#785223"

    Text {
        id: txtLabel
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 10
        text: "过号呼叫:"
        font.family: "FZLanTingHei-B-GBK"
        font.pixelSize: 28
        color: "white"
    }

    Rectangle {
        id: showNamesFrame
        clip: true
        color: "transparent"
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: txtLabel.right
        anchors.margins: 10
        anchors.right: parent.right

        Row{
            id: show
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 10

            Row{
                id: showNames
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                spacing: 10
            }

            Row{
                id: showNameNext
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                spacing: 10
                visible: false
            }
        }

        Component {
            id: showComponet
            Text {
                id: txt
                anchors.verticalCenter: parent.verticalCenter
                font.family: "FZLanTingHei-B-GBK"
                font.pixelSize: 24
                color: "red"
            }
        }
    }

    /* 测试 */
    Timer {
        property int index: 0
        running: true
        repeat: true
        onTriggered: {
            index++
            addName("测试用户" + index);
            // console.debug(showNames.width, showNamesFrame.width);
            if(showNames.width > showNamesFrame.width) {
                scrollVisble.start();
                showNameNext.visible = true;
            }

            if(index >= 10) stop();
        }
    }

    Timer{
        property int pos: 0
        id: scrollVisble
        running: false
        interval: 100
        repeat: true
        onTriggered: {
            pos += 3;
            if(pos > showNames.width) {
                pos = 0;
            }

            show.x = -pos;
        }
    }

    Component.onCompleted: {
        addName("张三");
        addName("李四");
        addName("王五");
    }

    MouseArea {
        property int index: 0
        anchors.fill: parent
        onClicked: {
            removeName("测试用户" + index);
            index++;
        }
    }

    /* 添加项 */
    function addName(name) {
        var obj = showComponet.createObject(showNames);
        obj.text = name;
        // next
        obj = showComponet.createObject(showNameNext);
        obj.text = name;
    }

    function removeName(name) {
        var i;
        // 从next中删除
        for(i = 0; i < showNames.children.length; i++) {
            var obj = showNames.children[i];
            if(obj.text === name) {
                obj.destroy();
                break;
            }
        }
        // 从next中删除
        for(i = 0; i < showNameNext.children.length; i++) {
            var obj = showNameNext.children[i];
            if(obj.text === name) {
                obj.destroy();
                break;
            }
        }
        // 重新计算要不要移动
        if(showNames.width < showNamesFrame.width) {
            scrollVisble.stop();
            showNameNext.visible = false;
            show.x = 0;
        }
    }
}

