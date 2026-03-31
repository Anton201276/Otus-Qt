import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

Item {
    id: gauge
    width: 350; height: 350

    property real value_set: 0      // Текущее значение (0.0–1.0)
    property real value_valve: 0      // Текущее значение (0.0–1.0)
    property real minValue: 0  // Минимальное значение шкалы
    property real maxValue: 100 // Максимальное значение шкалы

    // Фон/шкала
    Rectangle {
        anchors.fill: parent
        color: "#2c3e50"
        radius: width / 2

        // Деления шкалы
        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                ctx.lineWidth = 2;
                ctx.strokeStyle = "white";

                for (var i = 0; i < 9; i++) {
                    var angle = (i * 30 + 150) * Math.PI / 180;
                    var startRadius = parent.width / 2 - 10;  // Начало линии (ближе к краю)
                    var endRadius = parent.width / 2 - 25;  // Конец линии (дальше от края)

                    ctx.beginPath();
                    ctx.moveTo(
                        parent.width / 2 + startRadius * Math.cos(angle),
                        parent.height / 2 + startRadius * Math.sin(angle)
                    );
                    ctx.lineTo(
                        parent.width / 2 + endRadius * Math.cos(angle),
                        parent.height / 2 + endRadius * Math.sin(angle)
                    );
                    ctx.stroke();
                }
            }
        }
    }

    // Центр вращения (точка крепления стрелки)
    Rectangle {
        width: 20; height: width
        color: "#33FFFF"
        anchors.centerIn: parent
        radius: width / 2
    }

    // Стрелка
    Rectangle {
        id: needle_set
        width: 6; height: parent.height / 2 - 20
        color: "#33FFFF"
        x: parent.width / 2 - width / 2  // Центрируем по горизонтали
        y: parent.height / 2 - height  // Центрируем точку вращения по вертикали
        transformOrigin: Item.Bottom  // Вращаем вокруг нижнего края
        rotation: (value_set * 240) - 120  // От -120° до +120°
    }

    Rectangle {
        id: needle_valve
        width: 6; height: parent.height / 2 - 20
        color: "#33FF22"
        x: parent.width / 2 - width / 2  // Центрируем по горизонтали
        y: parent.height / 2 - height  // Центрируем точку вращения по вертикали
        transformOrigin: Item.Bottom  // Вращаем вокруг нижнего края
        rotation: (value_valve * 240) - 120  // От -120° до +120°
    }

    Label {
        id: valveValue
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 25
        horizontalAlignment: Text.AlignHCenter
        text: "% " + qsTr("%1").arg((100 * value_valve).toFixed(2))
    }
}
