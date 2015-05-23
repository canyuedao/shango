import QtQuick 2.3

Rectangle {
    width: 1366
    height: 768
    color: "#DAB181" // "#785223"

    /* 标题栏 */
    MainFormTop {
        id: idTop
    }

    Rectangle {
        id: idCenter
        color: "transparent"
        anchors {
            left: parent.left
            right: parent.right
            top: idTop.bottom
            bottom: idBottom.top
        }

        MainFormLeft{
            id: idLeft
            width: parent.width / 2
        }

        MainFormRight {
            id: idRight
            anchors.left: idLeft.right
        }
    }

    /* 过号呼叫 */
    MainFormBottom{
        id: idBottom
    }
}
