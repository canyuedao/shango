import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1920
    height: 1080

    Loader {

        anchors.fill: parent
        source: "transfuse/Main.qml"
    }
}

