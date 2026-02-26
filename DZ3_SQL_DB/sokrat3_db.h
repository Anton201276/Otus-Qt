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

    bool loadDataSqlTables(const QSqlDatabase& dbc);


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

    bool dbIsOk_ = false;

};

#endif // SOKRAT3_DB_H
