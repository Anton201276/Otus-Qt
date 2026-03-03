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
    void Slot_GiveDB_TreeViewModel();
    void Slot_GiveDB_TableSqlModel(const QModelIndex& index);
    void Slot_OpenSQLiteDBFromFile(const QString& dp_file);

signals:
    void Signal_GetDB_TreeViewModel(QStandardItemModel* rootModel);
    void Signal_GetDB_ModuleTableModel(QStandardItemModel* propertiesModel);
    void Signal_GetDB_SokratDBModel(Sokrat3_DB* sokratDB);
    void Signal_GetDB_SqlDBModel(QSqlTableModel* sqlDBTable);


private:
    Sokrat3_DB* mySokratDB_;
};

#endif // CONTROL_DB_H
