#include "control_db.h"

Control_DB::Control_DB(QObject *parent) : QObject(parent)
{

}

void Control_DB::Slot_CreateDBFromFiles(const QString& path){
    qDebug() << "Сигнал создать БД" << "\n";
    mySokratDB_ = new Sokrat3_DB(path);
    emit Signal_GetDB_TreeViewModel(mySokratDB_->GetItemModel_SokratDB());
}

void Control_DB::Slot_GiveDB_ModuleTableModel(const QString& moduleName, const EModuleFields field) {
    emit Signal_GetDB_ModuleTableModel(mySokratDB_->GetItemModel_ModuleProperties(moduleName, field));
}
