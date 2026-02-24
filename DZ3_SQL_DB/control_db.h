#ifndef CONTROL_DB_H
#define CONTROL_DB_H

#include <QObject>
#include <QStandardItemModel>
#include <QString>
#include "sokrat3_db.h"
#include "CommonDefineType.h"

class Control_DB : public QObject
{
    Q_OBJECT
public:
    explicit Control_DB(QObject *parent = nullptr);

public slots:
    void Slot_CreateDBFromFiles(const QString& path);
    void Slot_GiveDB_ModuleTableModel(const QString& moduleName, const EModuleFields field);

signals:
    void Signal_GetDB_TreeViewModel(QStandardItemModel* rootModel);
    void Signal_GetDB_ModuleTableModel(QStandardItemModel* propertiesModel);

private:
    Sokrat3_DB* mySokratDB_;
    //QStandardItem* rootModel_;
    //QStandardItem* modulePropertiesModel_;
};

#endif // CONTROL_DB_H
