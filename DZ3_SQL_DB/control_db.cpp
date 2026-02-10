#include "control_db.h"

Control_DB::Control_DB(QObject *parent) : QObject(parent)
{

}

void Control_DB::Slot_GetPathSystemFile(QString path) {
    mySokratDB_ = new Sokrat3_DB(path);
    if (mySokratDB_->Get_DbIsOk()) {
        emit Signal_RootItemModel(rootModel_);
    }
}

void Control_DB::Slot_GetModuleNameField(QString moduleName, EModuleFields field) {

    emit Signal_PropertiesItemModel(modulePropertiesModel_);
}
