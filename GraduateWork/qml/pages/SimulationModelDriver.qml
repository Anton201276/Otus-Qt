import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

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
        text: qsTr("Параметры модели ЭП")
        font.pixelSize: Theme.fontSizeExtraLarge
    }
}
