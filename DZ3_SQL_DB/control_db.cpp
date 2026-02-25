#include "control_db.h"

Control_DB::Control_DB(QObject *parent) : QObject(parent)
{
    mySokratDB_ = nullptr;
}

void Control_DB::Slot_CreateDBFromFiles(const QString& path){
    if (mySokratDB_ == nullptr) {
        mySokratDB_ = new Sokrat3_DB(path);
        emit Signal_GetDB_SokratDBModel(mySokratDB_);
    }
}

void Control_DB::Slot_GiveDB_TreeViewModel() {
    mySokratDB_->createSQLite_SokratDB();
    emit Signal_GetDB_TreeViewModel(mySokratDB_->GetItemModel_SokratDB());
}

//void Control_DB::Slot_GiveDB_ModuleTableModel(const QString& moduleName, const EModuleFields field) {
//    emit Signal_GetDB_ModuleTableModel(mySokratDB_->GetItemModel_ModuleProperties(moduleName, field));
//}
