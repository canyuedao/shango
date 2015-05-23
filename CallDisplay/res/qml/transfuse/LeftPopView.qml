/************************************
** 呼叫弹出层
**
*************************************/

import QtQuick 2.3

Image {
    id: shade
    visible: false
    anchors.fill: parent;
    source: "../../image/popImg/shade.png"

    Image {
        id: pop
        width: parent.width-180;
        height: parent.height-180;
        anchors.centerIn: parent;
        source: "../../image/popImg/pop.png"

        Rectangle {
            width: pop.width;
            height:pop.height;
            color: "transparent"

            /* 医生照片 */
            Image {
                id: doctorImg;
                width: 422;
                height: 563;
                anchors{ top:parent.top; topMargin:30; left:parent.left; leftMargin: 30;}
                //source:      // doctorImage
            }


            Image {
                id: name
                source: "../../image/popImg/bottomShade.png"
                anchors{ top:doctorImg.bottom; left:parent.left;}

                /* 医生姓名信息 */
                Text {
                    id: doctorName
                    //text: "谢晓峰（副主任医生）";     // doctorName
                    color: "white";
                    font.family: "FZLanTingHei-B-GBK";
                    font.pointSize: 32;
                    font.bold: true;
                    anchors{ fill:parent; left: parent.left; leftMargin: 30; }
                    verticalAlignment: Text.AlignVCenter;
                }
            }

            Image {
                id: titleImg
                width: parent.width/2;
                height: parent.height/3;
                anchors{ top:parent.top; topMargin:parent.height*0.3; right:parent.right; rightMargin: 70;}
                source: "../../image/popImg/popTitle.png"

                Image {
                    id: img
                    width: 111;
                    height: 224;
                    anchors{ top:parent.top; topMargin:10; left:parent.left; leftMargin:10;}
                    source: "../../image/popImg/popState.png"

                    Text {
                        id: popStates
                        font.pointSize: 48
                        font.wordSpacing:30
                        wrapMode: Text.WordWrap             // 自动换行
                        color: "red";
                        font.family: "FZLanTingHei-B-GBK"
                        width: parent.width;
                        height: parent.height;
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                /* 显示 patient name */
                Text {
                   id: patient
                   //text: "王自如"          // patientName
                   font.pointSize: 42
                   color: "black";
                   font.family: "FZLanTingHei-B-GBK"
                   width: parent.width*3/4;
                   height: parent.height/2;
                   anchors { top: parent.top; right: parent.right; }
                   verticalAlignment: Text.AlignVCenter;
                }

                /* 显示病人当前状态 status */
                Text {
                    id: patientStatus
                    //text: "内科1诊室（2F-4）"     // doctorPlace
                    font.pointSize: 24
                    color: "black"
                    font.family: "FZLanTingHei-B-GBK"
                    width: parent.width*3/4;
                    height: parent.height/2;
                    anchors { top:patient.bottom; right: parent.right; }
                    verticalAlignment: Text.AlignVCenter;
                }

                Component.onCompleted: {
                    transfuseController.popViewInformation.connect(popViewInformation);
                }

                function popViewInformation(doctorPhone,doctorInfor,popState,patientName,seeDoctorSite){
                    doctorImg.source = doctorPhone
                    doctorName.text = doctorInfor
                    popStates.text = popState
                    patient.text = patientName
                    patientStatus.text = seeDoctorSite

                    shade.visible = true
                    popTimer.start();
                }
                Timer {
                    id: popTimer;
                    interval: 5000
                    onTriggered: {
                        popTimer.stop();
                        shade.visible = false;
                    }
                }
            }
        }

    }    
}
