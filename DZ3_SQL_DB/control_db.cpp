#include "control_db.h"

Control_DB::Control_DB(QObject *parent) : QObject(parent)
{

}

void Control_DB::Slot_CreateDBFromFiles(const QString& path){
    mySokratDB_ = new Sokrat3_DB(path);
}

void Control_DB::Slot_GiveDB_TreeViewModel() {
    emit Signal_GetDB_TreeViewModel(mySokratDB_->GetItemModel_SokratDB());
}

void Control_DB::Slot_GiveDB_ModuleTableModel(const QString& moduleName, EModuleFields field) {
    emit Signal_GetDB_ModuleTableModel(mySokratDB_->GetItemModel_ModuleProperties(moduleName, field));
}
