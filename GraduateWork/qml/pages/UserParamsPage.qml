import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1
import Aurora.Controls 1.0

Page {
    objectName: "UserParamsPage"
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
        text: qsTr("Параметры пользователя")
        font.pixelSize: Theme.fontSizeExtraLarge
    }

    AppBar {
            AppBarSpacer {}

            AppBarButton {
                context: "Печать документа"

                icon.source: "image://theme/icon-m-print"
            }
        }

    Button {
       id: id_btn_next
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.bottom: parent.bottom
       anchors.bottomMargin: 50
       border.color :  "#1199AA"
       border.highlightColor: "#FF00FF"
       text: "Далее"
       onClicked: {
           pageStack.push(Qt.resolvedUrl("ControlPage.qml"))
           console.log("Далее clicked")
       }
    }
}
