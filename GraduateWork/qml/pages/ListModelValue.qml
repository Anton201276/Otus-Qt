import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

ListView {
    id: topViewParams
    property string mdlName
    property string tblName
    property int rowTable: 0  // Будет хранить количество записей

    width: parent.width
    height: contentHeight  // Автоматически подстраивается под содержимое

    model: ListModel {
        id: valueModel
    }

    delegate: Column {
        width: parent.width
        spacing: 5

        TextField {
            //width: parent.width - id_lbl_TypeDrive.width - left_margin_item - right_margin_item
            label: name
            text: nowValue
            horizontalAlignment: TextInput.AlignRight
            readOnly: true
        }

//        Row {
//            Label {
//                //anchors.horizontalCenter: parent.horizontalCenter
//                horizontalAlignment: TextInput.AlignLeft
//                text: name
//            }


//            Label {
//                //anchors.horizontalCenter: parent.horizontalCenter
//                horizontalAlignment: TextInput.AlignRight
//                text: nowValue
//            }
//        }

        Row {
            Label {
                horizontalAlignment: TextInput.AlignLeft
                text: "Минимум - "
            }

            Label {
                text: minValue
                horizontalAlignment: TextInput.AlignRight
            }
        }

        Row {
            Label {
                horizontalAlignment: TextInput.AlignLeft
                text: "Максимум - "
            }

            Label {
                //width: parent.width - id_lbl_TypeDrive.width - left_margin_item - right_margin_item
                text: maxValue
                horizontalAlignment: TextInput.AlignRight
            }
        }
    }

    function getDataFromDB() {
        // Получаем количество записей из БД
        rowTable = controlSim.invoke_execute_QueryDB_ByName(tblName);

        if (rowTable <= 0) {
            console.log("getDataFromDB: Нет данных для таблицы " + tblName);
            return;
        }

        // Очищаем модель перед заполнением
        valueModel.clear();

        // Заполняем модель данными, получая каждую запись по индексу
        for (var i = 0; i < rowTable; i++) {
            var val_name = controlSim.invoke_get_Value_ByIndex(i, "Название");
            var now_value = controlSim.invoke_get_Value_ByIndex(i, "Значение");
            var min_value = controlSim.invoke_get_Value_ByIndex(i, "Минимальное");
            var max_value = controlSim.invoke_get_Value_ByIndex(i, "Максимальное");

            // Добавляем элемент в модель (передаём объект, а не массив)
            valueModel.append({
                name: val_name,
                nowValue: now_value,
                minValue: min_value,
                maxValue: max_value
            });
        }

        console.log("getDataFromDB: Загружено " + rowTable + " записей");
    }
}
