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

    Label {
        id: top_lbl
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 120
        //anchors.leftMargin: 120
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
       anchors.horizontalCenter: parent.anchors.horizontalCenter
       label: "электропривода"
       currentIndex: 0
       menu: ContextMenu {
           MenuItem { text: "Линейный" }
           MenuItem { text: "Четвертьоборотный" }
           MenuItem { text: "Многооборотный" }
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

    Button {
       id: id_btn_start
       text: "Подключиться"
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.top: id_pb_connect.bottom
       anchors.topMargin: 20
       onClicked: {
           id_pb_connect.value = 0
           id_connect_Timer.running = true
           id_lbl_fake.visible = true
           console.log(dataFilePath, " Тип ЭП - ", id_cb_type.value)
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

            // Если прогресс достиг 100 %, останавливаем таймер
            if (id_pb_connect.value >= id_pb_connect.maximumValue) {
                console.log("Таймер завершён!")
                running = false
            }
        }
    }

    Label {
        id: id_lbl_titleParams
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top:id_btn_start.bottom
        anchors.topMargin: 50
        width: parent.width
        text: qsTr("Параметры ЭП")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Theme.fontSizeExtraLarge
        visible: true

    }

    Button {
       id: id_btn_next
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.bottom: parent.bottom
       anchors.bottomMargin: 50
       text: "Далее"
       onClicked: console.log(dataFilePath, " Тип ЭП - ", id_cb_type.value)
    }


}
