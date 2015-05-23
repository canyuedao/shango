import QtQuick 2.3
import My 1.0

Rectangle {
    width: 360
    height: 360

    Column{
        anchors.centerIn: parent
        spacing: 10

        Rectangle {
            width: 300
            height: 40
            color: "#eaf5ed"
            Text {
                anchors.verticalCenter: parent.verticalCenter
                id: info_1
                text: "id: 1\r\nvalue: 0"
            }

            Text {
                id: time_1
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: "00-00-00"
            }
        }

        Rectangle {
            width: 300
            height: 40
            color: "#e1eaf9"
            Text {
                anchors.verticalCenter: parent.verticalCenter
                id: info_2
                text: "id: 2\r\nvalue: 0"
            }

            Text {
                id: time_2
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: "00-00-00"
            }
        }

        Rectangle {
            width: 300
            height: 40
            color: "#eaf5ed"
            Text {
                anchors.verticalCenter: parent.verticalCenter
                id: info_3
                text: "id: 3\r\nvalue: 0"
            }

            Text {
                id: time_3
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: "00-00-00"
            }
        }

        Rectangle {
            width: 300
            height: 40
            color: "#e1eaf9"
            Text {
                anchors.verticalCenter: parent.verticalCenter
                id: info_4
                text: "id: 4\r\nvalue: 0"
            }

            Text {
                id: time_4
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: "00-00-00"
            }
        }

        Rectangle {
            width: 300
            height: 40
            color: "#eaf5ed"
            Text {
                anchors.verticalCenter: parent.verticalCenter
                id: info_5
                text: "id: 5\r\nvalue: 0"
            }

            Text {
                id: time_5
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: "00-00-00"
            }
        }

        Text {
            id: txt
            color: "red"
        }
    }


    Heart {
        onError: {
            txt.text = str;
            txt.color = "red";
        }

        onRecv: {
            var str =  "id: " + id.toString()
                    + "\r\nvalue: " + sp.toString();
            switch(id){
            case 1: info_1.text = str; time_1.text = getTime(); break;
            case 2: info_2.text = str; time_2.text = getTime(); break;
            case 3: info_3.text = str; time_3.text = getTime(); break;
            case 4: info_4.text = str; time_4.text = getTime(); break;
            case 5: info_5.text = str; time_5.text = getTime(); break;
            default: txt.text = str; txt.color = "red"; break;
            }

            info_1.color = "blank";
            info_2.color = "blank";
            info_3.color = "blank";
            info_4.color = "blank";
            info_5.color = "blank";
            switch(id){
            case 1: info_1.color = "red"; break;
            case 2: info_2.color = "red"; break;
            case 3: info_3.color = "red"; break;
            case 4: info_4.color = "red"; break;
            case 5: info_5.color = "red"; break;
            }
        }

        onInfo: {
            txt.text = str;
            txt.color = "green";
        }
    }

    function getTime() {
        var dt = new Date()
        return dt.toLocaleString(Qt.locale(), "hh:mm:ss");
    }
}
