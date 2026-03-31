import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

Item {
    width: 200;
    height: 200

    property string closeColor: "#ffa500"
    property string openColor: "#229911"
    property string valveStatus: "по средине"

        Label {
            id: top_lbl
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            //anchors.leftMargin: 120
            width: parent.width
            text: qsTr("Статус ЭП")
            font.pixelSize: Theme.fontSizeExtraLarge
        }

            Row {
                anchors.top: top_lbl.bottom
                anchors.topMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter
                Rectangle {
                    id: recClose
                    width: 80; height: 80
                    radius: width / 2
                    color: closeColor
                    x: parent.width / 2 - 250
                    y: parent.height / 2 - 50
                }

                Label {
                    //id: top_lbl
                    horizontalAlignment: Text.AlignHCenter
                    //anchors.leftMargin: 120
                    width: parent.width
                    text: valveStatus
                    font.pixelSize: 20
                }

                Rectangle {
                    id: recOpen
                    width: 80; height: 80
                    radius: width / 2
                    color: openColor
                    x: parent.width / 2 + 250
                    y: parent.height / 2 - 50
                }
            }

}
