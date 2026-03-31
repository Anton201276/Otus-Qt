import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

Page {
    objectName: "SimulationModelPage"
    allowedOrientations: Orientation.All
    id: page

    PageHeader { title: qsTr("Параметры модели ЭП") }

    ComboBox {
       id: id_cb_pageselect
       anchors.top: parent.top
       anchors.topMargin: 60
       anchors.left: parent.left
       anchors.leftMargin: 50
       anchors.horizontalCenter: parent.horizontalCenter
       label: "Перейти к странице"
       currentIndex: 0
       menu: ContextMenu {
           MenuItem { text: "выбрать" }
           MenuItem { text: "На главную" }
           MenuItem { text: "Управления ЭП" }
           MenuItem { text: "Пользователя" }
           MenuItem { text: "Заводские" }
       }

       onCurrentIndexChanged: {
           console.log("ComboBox clicked", id_cb_pageselect.currentIndex)
           if (id_cb_pageselect.currentIndex === 1) {
               while (pageStack.depth > 1) {
                   pageStack.pop()
               }
               console.log("MainPage clicked")
           }
           else if (id_cb_pageselect.currentIndex === 2) {
               pageStack.replace(Qt.resolvedUrl("ControlPage.qml"))
               console.log("ControlPage clicked")
           }
           else if (id_cb_pageselect.currentIndex === 3) {
               pageStack.replace(Qt.resolvedUrl("UserParamsPage.qml"))
               console.log("UserParamsPage clicked")
           }
           else {
               pageStack.replace(Qt.resolvedUrl("PlantParamsPage.qml"))
               console.log("PlantParamsPage clicked")
           }
       }
    }
}

//    ButtonLayout {
//        id: id_btn_layout_next
//        //anchors.horizontalCenter: parent.horizontalCenter
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 50
//        visible: true
//        //anchors.top: mainColumn.bottom
//        //anchors.topMargin: top_margin_item

//        Button {
//           id: id_btn_main_page
//           text: "На главную"
//           border.color :  "#1199AA"
//           border.highlightColor: "#FF99FF"
//           onClicked: {
//               onClicked: pageStack.pop()
//               while (pageStack.depth > 1) {
//                           pageStack.pop()
//               }
//               console.log("MainPage clicked")
//           }
//        }

//        Button {
//           id: id_btn_control_drive
//           text: "Управление ЭП"
//           border.color :  "#1199AA"
//           border.highlightColor: "#FF99FF"
//           onClicked: {
//               onClicked: pageStack.pop()
//               pageStack.push(Qt.resolvedUrl("ControlPage.qml"))
//               console.log("ControlPage clicked")
//           }
//        }


//        Button {
//           id: id_btn_user_settigs
//           text: "Заводские"
//           border.color :  "#1199AA"
//           border.highlightColor: "#FF99FF"
//           onClicked: {
//               onClicked:
//               pageStack.pop()
//               pageStack.push(Qt.resolvedUrl("PlantParamsPage.qml"))
//               console.log("PlantParamsPage clicked")
//           }
//        }

//        Button {
//           id: id_btn_simulate_model
//           text: "Пользователя"
//           border.color :  "#1199AA"
//           border.highlightColor: "#FF99FF"
//           onClicked: {
//               onClicked:
//               pageStack.pop()
//               pageStack.push(Qt.resolvedUrl("UserParamsPage.qml"))
//               console.log("UserParamsPage clicked")
//           }
//        }
//    }
