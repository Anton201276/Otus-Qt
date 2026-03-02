#ifndef SOKRAT3_DB_H
#define SOKRAT3_DB_H

#include <QDebug>
#include <QString>
#include <QFile>
#include <QHash>
#include <QVector>
#include <QStandardItemModel>
#include <QtSql>
#include <QSqlDatabase>

#include "CommonDefineType.h"


class Sokrat3_DB
{
public:
    Sokrat3_DB(const QString db_path);
    ~Sokrat3_DB();

    void GetListModulesName(QStringList& list) const;
    void GetListModulesDesc(QStringList& list) const;

    QStandardItemModel* GetItemModel_SokratDB() ;
    QStandardItemModel* GetItemModel_ModuleProperties(const QString& mdl, EModuleFields prop);
    QSqlTableModel* GetItemModel_FromSqlDataBase(const QModelIndex& index);

    bool Get_DbIsOk() const {
        return dbIsOk_;
    }

    void createSQLite_SokratDB();

private:
    bool CreateDB_FromFiles();
    bool ParseModuleDescFile(const QString& module_name);
    bool ParseItemModule(SModulePropertiesDesc& module_properties, const QStringList& ptrStrings_ModuleDesc, quint16& cReadStrings, quint16& numProperties);

    bool CreateItemModelDB_FromFiles(SModuleDataBase& db);
    bool ParseModuleDescFile(const QString& module_name, SModuleDataBase& db);
    bool ParsePropertiesModule(QVector<SPropertyDesc>& module_properties, const QStringList& ptrStrings_ModuleDesc, quint16& cReadStrings, quint16& numProperties);

    void CreateDB_ItemModels(const SModuleDataBase& db_mdl);
    void CreateDB_ItemTreeView(const SModuleDataBase& db_mdl);
    //void CreateDB_ModuleItemTableView(const SModuleDataBase& db_mdl);
    void LoadDB_ModuleItemTableView(const QString& mdl, EModuleFields field, const QVector<SPropertyDesc>& mdl_prop);
    QList<QStandardItem*> LoadDB_RowProperties(const SPropertyDesc& property);

    bool copyModelToSqlTable(const QSqlDatabase& db, const QString& tableName);
    bool createMainSqlTable(const QSqlDatabase& dbc);
    bool createPlantUserSqlTable(const QSqlDatabase& dbc, const QString field);
    bool createDescSqlTable(const QSqlDatabase& dbc);
    bool createSqlTreeModel(const QSqlDatabase& dbc);
    bool addItemSqlTreeModel(const QSqlDatabase& dbc, QStandardItem* rootItem,  QString type);


private:

    QString db_path_{};
    QString sokrat_name_{};
    QString sokrat_date_{};
    QStringList modules_names_;
    QHash<QString,QString> list_modules_desc_;

    QStandardItemModel SokratTree_ItemModel_;
    QStandardItem SokratTree_RootItem_;
    QHash<QString,QStandardItemModel*> tableItem_modules_params_;
    QHash<QString,QStandardItemModel*> tableItem_modules_commands_;
    QHash<QString,QStandardItemModel*> tableItem_modules_signals_;

    QStandardItemModel SqlDB_TreeItemModel_;
    QStandardItem SqlDB_TreeRootItem_;
    QSqlDatabase sqlDB_;
    QSqlTableModel* sqlDB_TableModel_;

    bool dbIsOk_ = false;
    bool dbSqlIsOk_ = false;

};

#endif // SOKRAT3_DB_H
