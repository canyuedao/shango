/*
 * 系统配置页面(Configure)
 */
import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import Shango 1.0

Rectangle {
    width: 480
    height: 360
    // color: "transparent"
    color: "#5C401E"

    Column {
        spacing: 20
        anchors.topMargin: 100
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        // 标题
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "配置显示屏"
            font.pixelSize: 48
            font.family: "FZLanTingHei-B-GBK"
            color: "white"
        }

        Rectangle {
            color: "transparent"
            height: 50
            width: 10
        }

        Grid {
            columns: 2
            spacing: 20

            /* IP配置 */
            Text {
                text: "服务器IP:"
                font.pixelSize: 36
                font.family: "FZLanTingHei-B-GBK"
                color: "white"
                horizontalAlignment: Text.AlignRight
            }

            TextField{
                id: editIP
                width: 400
                font.pixelSize: 36
                font.family: "FZLanTingHei-B-GBK"
                text: config.ip
            }

            /* 端口配置 */
            Text {
                text: "服务器端口:"
                font.pixelSize: 36
                font.family: "FZLanTingHei-B-GBK"
                color: "white"
                horizontalAlignment: Text.AlignRight
            }

            TextField{
                id: editPort
                width: 200
                font.pixelSize: 36
                font.family: "FZLanTingHei-B-GBK"
                text: config.port
            }

            /* 显示屏类型选择 */
            Text {
                text: "类型:"
                font.pixelSize: 36
                font.family: "FZLanTingHei-B-GBK"
                color: "white"
                horizontalAlignment: Text.AlignRight
            }

            ComboBox{
                id: cbType
                width: 400
                height: 60
                style: ComboBoxStyle{
                    //font.pixelSize: 36
                    //font.family: "FZLanTingHei-B-GBK"
                }

                model: ListModel {
                    id: cbTypeItems
                    ListElement { text: "输液呼叫显示屏"; type: 1}
                }

            }
        }

        // 占位符
        Rectangle{
            color: "transparent"
            height: 50
            width: 10
        }

        /* 应用按钮 */
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 400
            height: 60
            style: ButtonStyle{
                label: Text{
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: "应用"
                    font.pixelSize: 36
                    font.family: "FZLanTingHei-B-GBK"
                }
            }

            onClicked: {
                config.ip = editIP.text
                config.port = editPort.text
                config.type = cbTypeItems.get(cbType.currentIndex).type;
                config.saveConfigure();
                // 连接服务器
                retryConnect();
            }
        }
    }

    /* 配置控制器 */
    ConfigureController {
        id: config
    }
}

