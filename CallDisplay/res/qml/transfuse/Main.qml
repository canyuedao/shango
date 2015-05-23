
import QtQuick 2.3
import QtQuick.Controls 1.2
import Shango   1.0

Rectangle {
    width: 1920;
    height: 1080;

    Loader {
        z: 0
        id: base_full_screen;
        anchors.fill: parent;
        source: "MainBase.qml"
        focus: true;
    }

    /* 输液控制器 */
    TransfuseController {
        id: transfuseController

    }

    Timer {
       interval: 15000
       running: true
       repeat: true
       triggeredOnStart: false
       onTriggered: {
           transfuseController.popViewInformation("../../image/popImg/doctor.png",
                                                  "谢晓峰（副主任医生）",
                                                  "输液",
                                                  "王自如",
                                                  "内科1诊室（2F-4）");
       }
    }
}
