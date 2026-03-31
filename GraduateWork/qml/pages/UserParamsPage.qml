import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1
import Aurora.Controls 1.0

Page {
    objectName: "UserParamsPage"
    allowedOrientations: Orientation.All
    id: page

    PageHeader { title: qsTr("Параметры пользователя") }

    property int top_margin_item: 60
    property int left_margin_item: 30
    property int right_margin_item: 30
    property int bottom_margin_item: 30

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
           MenuItem { text: "Заводские" }
           MenuItem { text: "Модель ТПА" }
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
               pageStack.replace(Qt.resolvedUrl("PlantParamsPage.qml"))
               console.log("PlantParamsPage clicked")
           }
           else {
               pageStack.replace(Qt.resolvedUrl("SimulationModelPage.qml"))
               console.log("SimulationModel clicked")
           }
       }
    }

    Column {
        id: mainColumn
        anchors.top: id_cb_pageselect.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        //anchors.bottom: id_btn_layout_next.top
        //anchors.bottomMargin: 50
        spacing: 20

        //SilicaFlickable {
            //anchors.fill: parent
            //anchors.top: parent.top
            //anchors.topMargin: 100
            //contentHeight: mainColumn.height
            //anchors.bottom: parent.bottom

            Column {
                id: userColumn
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: Theme.fontSizeExtraLarge
                    text: "Защиты"
                }

                ListModelValue {
                    id: listDefenceParams
                    width: parent.width
                    tblName: "mdlParamsDefence"

                }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: Theme.fontSizeExtraLarge
                    text: "Моментная муфта"
                }

                ListModelValue {
                    id: listTorqueParams
                    width: parent.width
                    tblName: "mdlParamsTorque"
                }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: Theme.fontSizeExtraLarge
                    text: "Контроль движения"
                }

                ListModelValue {
                    id: listValveParams
                    width: parent.width
                    tblName: "mdlParamsValve"
                }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: Theme.fontSizeExtraLarge
                    text: "Настройки управления"
                }

                ListModelValue {
                    id: listControlParams
                    width: parent.width
                    tblName: "mdlParamsControl"
                }
            }
        }
    //}

    Component.onCompleted: {
        listDefenceParams.getDataFromDB()
        listTorqueParams.getDataFromDB()
        listValveParams.getDataFromDB()
        listControlParams.getDataFromDB()
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
//               while (pageStack.depth > 1) {
//                           pageStack.pop()
//               }
//               console.log("MainPage clicked")
//           }
//        }


//        Button {
//           id: id_btn_user_settigs
//           text: "Заводские"
//           border.color :  "#1199AA"
//           border.highlightColor: "#FF99FF"
//           onClicked: {
//               pageStack.push(Qt.resolvedUrl("PlantParamsPage.qml"))
//               console.log("PlantParamsPage clicked")
//           }
//        }

//        Button {
//           id: id_btn_control_drive
//           text: "Управление ЭП"
//           border.color :  "#1199AA"
//           border.highlightColor: "#FF99FF"
//           onClicked: {
//               pageStack.push(Qt.resolvedUrl("ControlPage.qml"))
//               console.log("ControlPage clicked")
//           }
//        }

//        Button {
//           id: id_btn_simulate_model
//           text: "Модель ТПА"
//           border.color :  "#1199AA"
//           border.highlightColor: "#FF99FF"
//           onClicked: {
//               pageStack.push(Qt.resolvedUrl("SimulationModelPage.qml"))
//               console.log("SimulationModel clicked")
//           }
//        }
//    }
