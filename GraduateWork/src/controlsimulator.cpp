#include "controlsimulator.h"

ControlSimulator::ControlSimulator(QObject *parent) : QObject(parent)
{
    mySokratDB_ = nullptr;
}

void ControlSimulator::slot_onMessageReceived(const QString &message) {
    qDebug() << "Получено сообщение из QML:" << message << "\n";
    if (mySokratDB_ == nullptr) {
        mySokratDB_ = new Sokrat3_DB(message);
        //emit Signal_GetDB_SokratDBModel(mySokratDB_);
    }

}

void ControlSimulator::slot_onDataReceived(const QString &name, int age) {
    qDebug() << "Получены данные из QML::" << name << ", номер:" << age;
}

int ControlSimulator::invoke_execute_QueryDB_ByName(const QString& db_Name) {
    return mySokratDB_->Execute_QueryDB_ByName(db_Name);
}

QVariant ControlSimulator::invoke_get_Value_ByIndex(int row, const QString& col) {
    return mySokratDB_->Get_Value_ByIndex(row, col);
}
