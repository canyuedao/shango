import QtQuick 2.4
import QtQuick.Window 2.2
import Shango 1.0

Window {
    visible: true
    width: 960
    height: 540
//    visibility: Window.FullScreen;


    Rectangle {
        width: 1920
        height: 1080
        scale: 0.5
        transformOrigin: Item.TopLeft
        color: "#5C401E"

        /* 加载显示屏 */
       Loader {
           id: mainLoader
           anchors.fill: parent
           source: "Loading.qml"
        }
    }

   /* 本地存储对像 */
   MainController {
       id: mainController
       /* 连接服务器成功，并返回当前显示屏的类型 */
       onLogin: {
           switch(type){
           case 0:
               mainLoader.source = "Configure.qml"
               break;
           case 1:
               mainLoader.source = "transfuse/Main.qml"
               break;
           default:
               mainLoader.source = "WaitRetry.qml"
               break;
           }
       }
   }

   Component.onCompleted: {
       mainController.start();
   }

   /* 启动重新连接流程 */
   function retryConnect() {
       mainLoader.source = "Loading.qml";
       mainController.start();
   }
}
