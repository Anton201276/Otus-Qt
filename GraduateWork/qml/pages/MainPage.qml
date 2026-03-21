import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All
    id: id_mainPage

    property string dataFilePath: StandardPaths.data
    property string typeDrive


    PageHeader {
        objectName: "pageHeader"
        title: qsTr("Sokrat Tester")
        extraContent.children: [
            IconButton {
                objectName: "aboutButton"
                icon.source: "image://theme/icon-m-about"
                anchors.verticalCenter: parent.verticalCenter

                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        ]
    }

    Column {
        anchors.centerIn: parent
        width: parent.width - 2 * Theme.horizontalPageMargin

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            text: qsTr("Выберите тип")
            font.pixelSize: Theme.fontSizeExtraLarge
        }

        ComboBox {
            id: id_cb_type
            //anchors.horizontalCenter: parent.anchors.horizontalCenter
            label: "электропривода"
            currentIndex: 0
            menu: ContextMenu {
                MenuItem { text: "Линейный" }
                MenuItem { text: "Четвертьоборотный" }
                MenuItem { text: "Многооборотный" }
            }
        }

        Button {
           text: "Подключиться"
           anchors.horizontalCenter: parent.horizontalCenter
           onClicked: {
               id_pb_connect.value = 0
               id_connect_Timer.running = true
               id_lbl_fake.visible = true
               console.log(dataFilePath, " Тип ЭП - ", id_cb_type.value)
           }
        }

        ProgressBar {
            id: id_pb_connect
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - Theme.horizontalPageMargin
            minimumValue: 0
            maximumValue: 100
            value: 0
            valueText: value + "%"
        }

        Label {
            id: id_lbl_fake
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            text: qsTr("Имитация Bluetooth считывания")
            font.pixelSize: 40
            visible: false
        }

        Timer {
            id: id_connect_Timer
            interval: 50
            repeat: true
            running: false

            onTriggered: {
                // Увеличиваем прогресс на долю от общего времени за один интервал
                id_pb_connect.value += 2.5

                // Если прогресс достиг 100 %, останавливаем таймер
                if (id_pb_connect.value >= id_pb_connect.maximumValue) {
                    console.log("Таймер завершён!")
                    running = false
                    id_lbl_fake.visible = false
                }
            }
        }

        Label {
            id: id_lbl_titleParams
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            text: qsTr("Параметры электропривода")
            font.pixelSize: Theme.fontSizeExtraLarge
            visible: true
        }


        Button {
           id: id_btn_start
           anchors.horizontalCenter: parent.horizontalCenter
           //anchors.bottom: parent.bottom

           text: "Продолжить"
           onClicked: console.log(dataFilePath, " Тип ЭП - ", id_cb_type.value)
        }

    }
}
