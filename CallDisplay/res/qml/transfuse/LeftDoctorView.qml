/************************************
** 视窗左边专家介绍展示页
** 显示当天值班的专家和护士的基本信息
*************************************/

import QtQuick 2.3

Rectangle {
    id: expertViewId;
    anchors.fill: parent;

    property int textSize: 18;

    /* header */
    Component {
        id: grid_header;

        Image {
            width: expertViewId.width;
            height: expertViewId.height/12;
            source: "../../image/leftTitleBottom.png"

            Image {
                width: parent.width-16;
                height: parent.height-10;
                anchors { top: parent.top; left: parent.left; topMargin: 5; leftMargin: 8;}
                source: "../../image/leftTitle.png"

                Text {text: "科室医务人员介绍"; color: "white"; font.family: "FZLanTingHei-B-GBK"; font.pointSize: 32; font.bold: true; anchors.top: parent.top; anchors.topMargin:10; anchors.horizontalCenter: parent.horizontalCenter; }
            }

        }
    }

    /* 医师介绍模版 */
    Component {
        id: grid_model;
        Rectangle {
            width: gridView.cellWidth;
            height: gridView.cellHeight;

            /* 医师照片图 */
            Image {
                source: portrait;
                width: parent.width*0.8;
                height: parent.height*0.8;
                anchors{ top:parent.top; topMargin:parent.height*0.1; left:parent.left; leftMargin: parent.width*0.1;}

                Image {
                    id: doctorShade;
                    anchors{ left: parent.left; right: parent.right; bottom: parent.bottom;}
                    source: "../../image/doctorShade.png" ;

                    Column {
                        anchors.fill: parent;
                        spacing: 0;
                        /* 医生姓名 */
                        Text {
                            text: "医生："+doctor_name;
                            color: "white";
                            height: parent.height/3;
                            anchors{ left: parent.left; leftMargin: parent.width/20;}
                            font.family: "FZLanTingHei-B-GBK";
                            font.pointSize: textSize;
                            verticalAlignment:Text.AlignVCenter;            // 上下居中
                        }

                        /* 职称名称 */
                        Text {
                            text: "职称："+job_name;
                            color: "white";
                            height: parent.height/3;
                            anchors{ left: parent.left; leftMargin: parent.width/20;}
                            font.family: "FZLanTingHei-B-GBK";
                            font.pointSize: textSize;
                            verticalAlignment:Text.AlignVCenter;            // 上下居中
                        }

                        /* 科室名称 */
                        Text {
                            text: "科室："+office_name;
                            color: "white";
                            height: parent.height/3;
                            anchors{ left: parent.left; leftMargin: parent.width/20;}
                            font.family: "FZLanTingHei-B-GBK";
                            font.pointSize: textSize;
                            verticalAlignment:Text.AlignVCenter;            // 上下居中
                        }
                    }
                }
            }
        }
    }

    //
    GridView {
        id: gridView;
        anchors.fill: parent;
        cellWidth: parent.width/4;
        cellHeight: parent.height/2-parent.height/24;
        interactive: false // 禁止交互

        delegate: grid_model;                               // 内容模版定义
        header: grid_header;                                // 作为标题
        model: transfuseController.modelDoctorQueue;        // 数据列表

    }

    // 定时刷新数据
    Timer {
        id: timer;
        property int page: 0
        interval:cpp.switchinterval
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            // 定时刷新数据
            transfuseController.upDoctorQueueModel(page++)
        }
    }

    Component.onCompleted: {
        transfuseController.dataLoadComplate.connect(onErr)
    }

    function onErr(tp, err) {
        if(1 == tp && 0 != err) {
            console.debug("transfuseController.Doctor end");
            timer.stop();
        }
    }
}

