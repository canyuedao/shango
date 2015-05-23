import QtQuick 2.0

MainFormRow {
    id: row

    Timer {
        property bool switchColor: false
        repeat: true
        triggeredOnStart: true
        running: true
        interval: 800
        onTriggered: {
            switchColor = !switchColor;
            if(switchColor) {
                row.textColor = "green"
                row.color = "red"
            } else {
                row.textColor = "white"
                row.color = "green"
            }
        }
    }
}

