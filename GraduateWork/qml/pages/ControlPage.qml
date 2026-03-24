import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

Page {
    objectName: "ControlPage"
    allowedOrientations: Orientation.All
    id: page

    PageHeader { title: qsTr("СократОператор") }

    Label {
        id: top_lbl
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 120
        anchors.leftMargin: 120
        width: parent.width
        text: qsTr("Управление ЭП ТПА")
        font.pixelSize: Theme.fontSizeExtraLarge
    }

//    Column {
//        anchors.centerIn: parent
//        width: parent.width - 2 * Theme.horizontalPageMargin

//        Label {
//            width: parent.width
//            text: qsTr("Введите данные об аккаунте")
//            font.pixelSize: Theme.fontSizeExtraLarge
//        }

//        Label {
//            width: parent.width
//            text: qsTr("")
//            font.pixelSize: Theme.fontSizeExtraLarge
//        }

//        TextField {
//            id: tf_faml
//            width: parent.width
//            placeholderText: qsTr("Фамилия")
//            validator: RegExpValidator {
//                    regExp: /^[А-яA-z]{1,20}$/
//            }
//            EnterKey.enabled: !errorHighlight
//            EnterKey.iconSource: "image://theme/icon-m-enter-next"
//            EnterKey.onClicked: tf_name.focus = true
//        }

//        TextField {
//            id: tf_name
//            width: parent.width
//            placeholderText: qsTr("Имя")
//            validator: RegExpValidator {
//                    regExp: /^[А-яA-z]{1,20}$/
//            }
//            EnterKey.enabled: !errorHighlight
//            EnterKey.iconSource: "image://theme/icon-m-enter-next"
//            EnterKey.onClicked: tf_father.focus = true
//        }

//        TextField {
//            id: tf_father
//            width: parent.width
//            placeholderText: qsTr("Отчество")
//            validator: RegExpValidator {
//                    regExp: /^[А-яA-z]{1,20}$/
//            }
//            EnterKey.enabled: !errorHighlight
//            EnterKey.iconSource: "image://theme/icon-m-enter-next"
//            EnterKey.onClicked: tf_mail.focus = true
//        }

//        TextField {
//            id: tf_mail
//            width: parent.width
//            placeholderText: qsTr("ivan.ivanov@rumail.ru")
//            validator: RegExpValidator {
//               regExp: /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/
//            }
//            EnterKey.enabled: !errorHighlight
//            EnterKey.iconSource: "image://theme/icon-m-enter-next"
//            EnterKey.onClicked: cb_prof.focus = true
//        }



//        ComboBox {
//            id: cb_prof
//            label: "Должность"
//            currentIndex: 0
//            menu: ContextMenu {
//                MenuItem { text: "Рабочий" }
//                MenuItem { text: "Мастер" }
//                MenuItem { text: "Начальник участка" }
//                MenuItem { text: "Начальник цеха" }
//                MenuItem { text: "Инженер" }
//                MenuItem { text: "Главный инженер" }
//            }
//        }


//        TextSwitch {
//            width: page.width
//            text: checked ? qsTr("ДА") : qsTr("НЕТ")
//            description: qsTr("Согласие на обработку персональных данных")
//            onCheckedChanged: {
//                if (checked) {
//                    console.log("Согласен")
//                }
//                else {
//                    console.log("не согласен")
//                }
//            }
//        }

//        TextSwitch {
//            width: page.width
//            text: checked ? qsTr("ДА") : qsTr("НЕТ")
//            description: qsTr("Согласие на рассылку уведомлений")
//            onCheckedChanged: {
//                if (checked) {
//                    console.log("Уведомлять")
//                }
//                else {
//                    console.log("Не уведомлять")
//                }
//            }
//        }

//        Item {
//            width: page.width
//            height: 40
//        }

//        Button {
//            id: btn_accept
//            anchors.horizontalCenter: parent.horizontalCenter
//            text: qsTr("Принять")

//            enabled: tf_faml.acceptableInput &&
//                             tf_name.acceptableInput &&
//                             tf_father.acceptableInput &&
//                             tf_mail.acceptableInput &&
//                             cb_prof.currentIndex !== -1
//            onClicked: console.log("Аккаунт создан")
//        }
//    }
    Button {
       id: id_btn_next
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.bottom: parent.bottom
       anchors.bottomMargin: 50
       border.color :  "#1199AA"
       border.highlightColor: "#FF00FF"
       text: "Далее"
       onClicked: {
           pageStack.push(Qt.resolvedUrl("SimulationModelDriver.qml"))
           console.log("Далее clicked")
       }
    }
}
