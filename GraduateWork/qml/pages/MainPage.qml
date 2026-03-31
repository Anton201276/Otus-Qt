import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All
    id: id_mainPage

    property string dataFilePath: StandardPaths.data
    property string typeDrive

    property string piturePath: "qrc:/picture/picture/Gusar1.jpg"
    property int pic_id: 1
    property int pause: 0

    property int top_margin_item: 60
    property int left_margin_item: 30
    property int right_margin_item: 30

    property int rowQuery: 0

    PageHeader {
        objectName: "pageHeader"
        title: qsTr("СократОператор")
        extraContent.children: [
            IconButton {
                objectName: "aboutButton"
                icon.source: "image://theme/icon-m-about"
                anchors.verticalCenter: parent.verticalCenter

                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        ]
    }

    Item {
        id: mainColumn
        //anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
        anchors.topMargin: 120

        Label {
            id: top_lbl
            horizontalAlignment: Text.AlignHCenter
            anchors.leftMargin: 120
            width: parent.width
            text: qsTr("Выберите тип")
            font.pixelSize: Theme.fontSizeExtraLarge
        }

        ComboBox {
           id: id_cb_type
           anchors.top: top_lbl.bottom
           anchors.topMargin: 20
           anchors.left: parent.left
           anchors.leftMargin: 50
           anchors.horizontalCenter: parent.horizontalCenter
           label: "подключения"
           currentIndex: 0
           menu: ContextMenu {
               MenuItem { text: "BlueTooth" }
               MenuItem { text: "IrDA" }
               MenuItem { text: "USB/RS485" }
           }
        }

        ProgressBar {
            id: id_pb_connect
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: id_cb_type.bottom
            anchors.topMargin: 10
            width: parent.width - Theme.horizontalPageMargin
            minimumValue: 0
            maximumValue: 100
            value: 0
            valueText: value + "%"
        }


        ButtonLayout {
            id: id_btn_layout
            anchors.top: id_pb_connect.bottom
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
               id: id_btn_connect
               text: "Подключиться"
               border.color :  "#1199AA"
               border.highlightColor: "#FF99FF"
               onClicked: {
                   id_pb_connect.value = 0
                   id_connect_Timer.running = true
                   messageSent(dataFilePath)
                   console.log(dataFilePath, " Тип ЭП - ", id_cb_type.value)
               }
            }

            Button {
               id: id_btn_settigs
               text: "Настройки"
               border.color :  "#1199AA"
               border.highlightColor: "#FF99FF"
               onClicked: {
                   pageStack.push(Qt.resolvedUrl("ConnectSettings.qml"))
                   dataSent(id_cb_type.value, id_cb_type.currentIndex)
                   console.log("Connect Settings clicked")
               }
            }
        }

        Image {
           id: imageDrive
           anchors.top: id_btn_layout.bottom
           anchors.topMargin: 40
           source: piturePath
           width: parent.width
           height: 700
           fillMode: Image.PreserveAspectFit
        }

        ButtonLayout {
            id: id_btn_layout_next
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            visible: false
            //anchors.top: paramsBlockDrive.bottom
            //anchors.topMargin: top_margin_item * 2

            Button {
               id: id_btn_plant_params
               text: "Заводские"
               border.color :  "#1199AA"
               border.highlightColor: "#FF99FF"
               onClicked: {
                   pageStack.push(Qt.resolvedUrl("PlantParamsPage.qml"))
                   console.log("PlantParamsPage clicked")
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
                   pageStack.push(Qt.resolvedUrl("SimulationModelPage.qml"))
                   console.log("SimulationModel clicked")
               }
            }
        }
    }

    Timer {
        id: id_connect_Timer
        interval: 50
        repeat: true
        running: false

        onTriggered: {
            // Увеличиваем прогресс на долю от общего времени за один интервал
            id_pb_connect.value += 2.5

            pause++

            if (pause >= 5) {
                pause = 0
                pic_id++
                if (pic_id > 3) {
                    pic_id = 1
                }

                if (pic_id == 1) {
                    piturePath = "qrc:/picture/picture/Gusar1.jpg"
                }
                else if (pic_id == 2) {
                    piturePath = "qrc:/picture/picture/Gusar2.jpg"
                }
                else {
                    piturePath = "qrc:/picture/picture/Gusar3.jpg"
                }
            }

            // Если прогресс достиг 100 %, останавливаем таймер
            if (id_pb_connect.value >= id_pb_connect.maximumValue) {
                console.log("Таймер завершён!")
                running = false
                id_btn_layout_next.visible = true

            }
            console.log("pause = ", pause)
            console.log("pic_id = ", pic_id)
            console.log("piturePath = ", piturePath)
        }
    }

}

/*

                rowQuery = controlSim.invoke_execute_QueryDB_ByName("mdlParamsBlock")
                console.log("строк в запросе = " + rowQuery)

                valueDB1 = controlSim.invoke_get_Value_ByIndex(0, "Название")
                valueDB2 = controlSim.invoke_get_Value_ByIndex(0, "Значение")
                console.log(valueDB1 + " = " + valueDB2)

                valueDB1 = controlSim.invoke_get_Value_ByIndex(1, "Название")
                valueDB2 = controlSim.invoke_get_Value_ByIndex(1, "Значение")
                console.log(valueDB1 + " = " + valueDB2)

                valueDB1 = controlSim.invoke_get_Value_ByIndex(2, "Название")
                valueDB2 = controlSim.invoke_get_Value_ByIndex(2, "Значение")
                console.log(valueDB1 + " = " + valueDB2)

        ColumnLayout {
            id: id_clm_lyt
            anchors.top: listModelPlantParams.bottom
            anchors.topMargin: top_margin_item * 2
            anchors.left: parent.left
            anchors.leftMargin: left_margin_item
            anchors.rightMargin: right_margin_item
            width: parent.width
            spacing: 60

            Label {
                //id: id_lbl_titleParams
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                text: qsTr("Основные параметры ЭП")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: Theme.fontSizeExtraLarge
                visible: true

            }

            Row {
                id: id_row_DataDrive
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                spacing: 15

                Label {
                    id: id_lbl_DataDrive
                    text: qsTr("Дата изготов - ")
                    font.pixelSize: Theme.fontSizeExtraLarge - 5
                }

                TextField {
                    id: id_tf_DataDrive
                    width: parent.width - id_lbl_DataDrive.width - left_margin_item - right_margin_item
                    placeholderText: "ГГГГ/ММ/ДД"
                    horizontalAlignment: TextInput.AlignRight
                    readOnly: true
                }
            }

            Row {
                id: id_row_TypeDrive
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                spacing: 15

                Label {
                    id: id_lbl_TypeDrive
                    text: qsTr("Тип привода - ")
                    font.pixelSize: Theme.fontSizeExtraLarge - 5
                }

                TextField {
                    id: id_tf_TypeDrive
                    width: parent.width - id_lbl_TypeDrive.width - left_margin_item - right_margin_item
                    placeholderText: "Л/В/П"
                    horizontalAlignment: TextInput.AlignRight
                    readOnly: true
                }
            }

            Row {
                id: id_row_TorqueDrive
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                spacing: 15

                Label {
                    id: id_lbl_TorqueDrive
                    text: qsTr("Макс. момент ЭП, Н*м - ")
                    font.pixelSize: Theme.fontSizeExtraLarge - 5
                }

                TextField {
                    id: id_tf_TorqueDrive
                    width: parent.width - id_lbl_TorqueDrive.width - left_margin_item - right_margin_item
                    placeholderText: "99999"
                    horizontalAlignment: TextInput.AlignRight
                    readOnly: true
                }
            }

            Row {
                id: id_row_SpeedDrive
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                spacing: 15

                Label {
                    id: id_lbl_SpeedDrive
                    text: qsTr("Макс. скор. ЭП, об/мин - ")
                    font.pixelSize: Theme.fontSizeExtraLarge - 5
                }

                TextField {
                    id: id_tf_SpeedDrive
                    width: parent.width - id_lbl_SpeedDrive.width - left_margin_item - right_margin_item
                    placeholderText: "99999"
                    horizontalAlignment: TextInput.AlignRight
                    readOnly: true
                }
            }

            Row {
                id: id_row_SpeedMotor
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                spacing: 15

                Label {
                    id: id_lbl_SpeedMotor
                    text: qsTr("Ном. скор ЭД, об/мин - ")
                    font.pixelSize: Theme.fontSizeExtraLarge - 5
                }

                TextField {
                    id: id_tf_SpeedMotor
                    width: parent.width - id_lbl_SpeedMotor.width - left_margin_item - right_margin_item
                    placeholderText: "99999"
                    horizontalAlignment: TextInput.AlignRight
                    readOnly: true
                }
            }

            Row {
                id: id_row_CurrentMotor
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                spacing: 15

                Label {
                    id: id_lbl_CurrentMotor
                    text: qsTr("Ном. ток ЭД, А - ")
                    font.pixelSize: Theme.fontSizeExtraLarge - 5
                }

                TextField {
                    id: id_tf_CurrentMotor
                    width: parent.width - id_lbl_CurrentMotor.width - left_margin_item - right_margin_item
                    placeholderText: "99999"
                    horizontalAlignment: TextInput.AlignRight
                    readOnly: true
                }
            }
        }
*/
