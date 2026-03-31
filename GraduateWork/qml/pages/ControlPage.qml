import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

Page {
    objectName: "ControlPage"
    allowedOrientations: Orientation.All
    id: page

    property string closeColor: "#ffa500"
    property string openColor: "#229911"
    property string middleColor: "#777799"

    property string valveStatus: "по средине"

    property int valveModelPosition: 500
    property int valveSetPosition: -1
    property int valveModelStatus: 0

    property int blinkCounter: 0
    property bool blinkLight: false

    PageHeader { title: qsTr("Управление ЭП") }

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
           MenuItem { text: "Заводские" }
           MenuItem { text: "Пользователя" }
           MenuItem { text: "Модель ТПА" }
       }

       onCurrentIndexChanged: {
           console.log("ComboBox clicked", id_cb_pageselect.currentIndex)
           id_modeling_Timer.running = false

           if (id_cb_pageselect.currentIndex === 1) {
               console.log("MainPage clicked")
               while (pageStack.depth > 1) {
                   pageStack.pop()
               }

           }
           else if (id_cb_pageselect.currentIndex === 2) {
               console.log("PlantParamsPage clicked")
               //pageStack.pop()
               pageStack.replace(Qt.resolvedUrl("PlantParamsPage.qml"))

           }
           else if (id_cb_pageselect.currentIndex === 3) {
               console.log("UserParamsPage clicked")
               //pageStack.pop()
               pageStack.replace(Qt.resolvedUrl("UserParamsPage.qml"))
           }
           else {
               console.log("SimulationModel clicked")
               //pageStack.pop()
               pageStack.replace(Qt.resolvedUrl("SimulationModelPage.qml"))
           }
       }
    }

    ButtonLayout {
        id: id_btn_layout_control
        anchors.top: id_cb_pageselect.bottom
        anchors.topMargin: 30
        visible: true

        Button {
           id: id_btn_open
           text: "Открыть"
           border.color :  "#1199AA"
           border.highlightColor: "#FF99FF"
           onClicked: {
               //setNewPosition(1000)
               valveSetPosition = 1000
               //console.log("QML newPosition clicked - ", 1000)
           }
        }


        Button {
           id: id_btn_close
           text: "Закрыть"
           border.color :  "#1199AA"
           border.highlightColor: "#FF99FF"
           onClicked: {
               //setNewPosition(0)
               valveSetPosition = 0
               //console.log("QML newPosition clicked - ", 0)
           }
        }

        Button {
           id: id_btn_stop
           text: "Стоп"
           border.color :  "#1199AA"
           border.highlightColor: "#FF99FF"
           onClicked: {
               //setNewPosition(valveModelPosition)
               valveSetPosition = valveModelPosition
               //console.log("QML newPosition clicked - ", valveModelPosition)
           }
        }

        Button {
           id: id_btn_goto
           text: "Установить"
           border.color :  "#1199AA"
           border.highlightColor: "#FF99FF"
           onClicked: {
               //setNewPosition(sliderSetPosition * 10)
               valveSetPosition = sliderSetPosition.value * 10
               console.log("QML newPosition id_btn_goto - ", sliderSetPosition.value * 10)
           }
        }
    }

    Column {
        id: mainColumn
        anchors.top: id_btn_layout_control.bottom
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter

        spacing: 30


        AnalogIndicator{
            id: positionIndicator
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.left: parent.left
            //anchors.leftMargin: 50
            value_set: 0.5  // 75 % шкалы
            value_valve: 0.0  // 75 % шкалы
        }

        Slider {
            id: sliderSetPosition
            width: page.width
            minimumValue: 0
            maximumValue: 100
            value: 50
            valueText: "% " + qsTr("%1").arg(value.toFixed(2))

            onValueChanged: {
                        console.log("Текущее значение:", value)
                        // Здесь можно добавить любую логику обработки
                        positionIndicator.value_set = value / 100
                    }

        }

        ValveStatusBar {
            id: statusBar
            anchors.horizontalCenter: parent.horizontalCenter
            closeColor: closeColor
            openColor: openColor
            valveStatus: "по средине"
        }
    }

    Timer {
        id: id_modeling_Timer
        interval: 50
        repeat: true
        running: false

        onTriggered: {
            // Увеличиваем прогресс на долю от общего времени за один интервал

            if (++blinkCounter > 10) {
                blinkCounter = 0
                blinkLight = blinkLight ? false : true
                //console.log("Таймер включен!")
                //console.log("Из модели положение = ", valveModelPosition, " -- ", positionIndicator.value_valve)
                //console.log("Из модели статус = ", valveModelStatus)
                if (valveSetPosition > -1) {
                    console.log("QML newPosition clicked - ", valveSetPosition)
                   setNewPosition(valveSetPosition)
                   valveSetPosition = -1
                }
            }
            //console.log("Таймер включен! - ", blinkCounter)
            valveModelPosition = controlSim.invoke_model_position()
            positionIndicator.value_valve = valveModelPosition / 1000
            valveModelStatus = controlSim.invoke_model_state()

            if (valveModelStatus == 0) {
                statusBar.valveStatus = "по средине"
                statusBar.closeColor = middleColor
                statusBar.openColor = middleColor
            }
            else if (valveModelStatus == 1) {
                statusBar.valveStatus = "Открыто"
                statusBar.closeColor = middleColor
                statusBar.openColor = openColor
            }
            else if (valveModelStatus == 2) {
                statusBar.valveStatus = "Закрыто"
                statusBar.closeColor = closeColor
                statusBar.openColor = middleColor
            }
            else if (valveModelStatus == 3) {
                statusBar.valveStatus = "Открывается"
                statusBar.closeColor = middleColor
                statusBar.openColor = blinkLight ? middleColor : openColor
            }
            else {
                statusBar.valveStatus = "Закрывается"
                statusBar.closeColor = blinkLight ? middleColor : closeColor
                statusBar.openColor = middleColor
            }

        }
    }

    Component.onCompleted: {
       id_modeling_Timer.running = true
    }
}
