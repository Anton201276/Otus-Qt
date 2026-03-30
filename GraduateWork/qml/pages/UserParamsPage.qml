import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1
import Aurora.Controls 1.0

Page {
    objectName: "UserParams"
    allowedOrientations: Orientation.All
    id: page

    PageHeader { title: qsTr("Параметры пользователя") }

    property int top_margin_item: 60
    property int left_margin_item: 30
    property int right_margin_item: 30
    property int bottom_margin_item: 30

    Column {
        id: mainColumn
        anchors.top: page.top
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
        //anchors.bottom: id_btn_layout_next.top
        //anchors.bottomMargin: 50
        spacing: 20

        SilicaFlickable {
            //anchors.fill: parent
            anchors.top: parent.top
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
    }

    ButtonLayout {
        id: id_btn_layout_next
        //anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        visible: true
        //anchors.top: mainColumn.bottom
        //anchors.topMargin: top_margin_item

        Button {
           id: id_btn_main_page
           text: "На главную"
           border.color :  "#1199AA"
           border.highlightColor: "#FF99FF"
           onClicked: {
               pageStack.push(Qt.resolvedUrl("MainPage.qml"))
               console.log("MainPage clicked")
           }
        }


        Button {
           id: id_btn_user_settigs
           text: "Пользователя"
           border.color :  "#1199AA"
           border.highlightColor: "#FF99FF"
           onClicked: {
               pageStack.push(Qt.resolvedUrl("UserParamsPage.qml"))
               console.log("UserParamsPage clicked")
           }
        }

        Button {
           id: id_btn_control_drive
           text: "Управление ЭП"
           border.color :  "#1199AA"
           border.highlightColor: "#FF99FF"
           onClicked: {
               pageStack.push(Qt.resolvedUrl("ControlPage.qml"))
               console.log("ControlPage clicked")
           }
        }

        Button {
           id: id_btn_simulate_model
           text: "Модель ТПА"
           border.color :  "#1199AA"
           border.highlightColor: "#FF99FF"
           onClicked: {
               pageStack.push(Qt.resolvedUrl("ControlPage.qml"))
               console.log("ControlPage clicked")
           }
        }
    }

    Component.onCompleted: {
        listDefenceParams.getDataFromDB()
        listTorqueParams.getDataFromDB()
        listValveParams.getDataFromDB()
        listControlParams.getDataFromDB()
    }

}
