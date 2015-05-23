import QtQuick 2.0

/* Top */
Rectangle {
    height: 69
    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
    }

    Image {
        source: "../images/top.png"
        anchors.fill: parent
    }

    /* Top - Left */
    Row{
        spacing: 10
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            leftMargin: 10
        }

        /* LOG图标 */
        Image {
            source: "../images/logo.png"
        }

        /* 医院名称 */
        Column {
            Text {
                text: "璧山中医院"
                color: "white"
                font.family: "FZLanTingHei-B-GBK"
                font.pixelSize: 32
            }

            Text {
                text: "Bishan Hospital of T.C.M"
                color: "white"
                font.family: "FZLanTingHei-B-GBK"
                font.pixelSize: 12
            }
        }

        /* 分隔条 */
        Image {
            source: "../images/bottomsplit.png"
        }

        /* 标题 */
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: "输液呼叫显示屏"
            color: "white"
            font.family: "FZLanTingHei-B-GBK"
            font.pixelSize: 32
        }
    }

    /* Top - Right */
    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
        id: timeShow
        color: "white"
        font.family: "FZLanTingHei-B-GBK"// "方正兰亭粗黑_GBK"
        font.pixelSize: 14
    }

    /* 定时显示时间屏 */
    Timer {
        repeat: true
        running: true
        onTriggered: {
            showTime();
        }
    }

    Component.onCompleted: {
        showTime();
    }

    /* 显示时间 */
    function showTime() {
        var dt = new Date()
        var str = dt.toLocaleString(Qt.locale(), "yyyy-MM-dd");
        str += "\r\n"
        str += getWeek(dt.getDay());
        str += "   "
        str += dt.toLocaleString(Qt.locale(), "hh:mm");

        timeShow.text = str;
    }

    /* 显示星期几 */
    function getWeek(w) {
        switch(w) {
        case 0: return "星期日";
        case 1: return "星期一";
        case 2: return "星期二";
        case 3: return "星期三";
        case 4: return "星期四";
        case 5: return "星期五";
        case 6: return "星期六";
        }
    }
}



