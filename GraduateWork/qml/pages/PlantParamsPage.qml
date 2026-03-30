import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1
import Aurora.Controls 1.0

Page {
    objectName: "PlantParams"
    allowedOrientations: Orientation.All
    id: page

    PageHeader { title: qsTr("Параметры заводские") }

    property int top_margin_item: 60
    property int left_margin_item: 30
    property int right_margin_item: 30
    property int bottom_margin_item: 30

    SilicaFlickable {
            anchors.fill: parent
            anchors.top: parent.top
            anchors.topMargin: 100
            contentHeight: mainColumn.height

            Column {
                id: mainColumn
                //anchors.fill: parent
                anchors.horizontalCenter: parent.horizontalCenter
                //horizontalAlignment: Text.AlignHCenter

                spacing: 20

                Column {
                    id: blockColumn
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20

                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: Theme.fontSizeExtraLarge
                        text: "Параметры блока"
                    }

                    ListModelValue {
                        id: listBlockParams
                        width: parent.width
                        tblName: "mdlParamsBlock"

                    }
                }

                Column {
                    id: driveColumn
                    //anchors.fill: parent
                    spacing: 20

                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: Theme.fontSizeExtraLarge
                        text: "Параметры привода"
                    }

                    ListModelValue {
                        id: listDriveParams
                        width: parent.width
                        tblName: "mdlParamsDrive"

                    }
                }



                ButtonLayout {
                    id: id_btn_layout_next
                    anchors.horizontalCenter: parent.horizontalCenter
                    //anchors.bottom: parent.bottom
                    //anchors.bottomMargin: 50
                    visible: true
                    //anchors.top: paramsBlockDrive.bottom
                    //anchors.topMargin: top_margin_item * 2

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
                       text: "Модель ТПА и ЭП"
                       border.color :  "#1199AA"
                       border.highlightColor: "#FF99FF"
                       onClicked: {
                           pageStack.push(Qt.resolvedUrl("ControlPage.qml"))
                           console.log("ControlPage clicked")
                       }
                    }
                }

            }


        }

    Component.onCompleted: {
        listBlockParams.getDataFromDB()
        listDriveParams.getDataFromDB()
    }

}
