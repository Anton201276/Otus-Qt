#ifndef SOKRAT3_DB_H
#define SOKRAT3_DB_H

#include <QDebug>
#include <QString>
#include <QFile>
#include <QHash>
#include <QStandardItemModel>

#include "CommonDefineType.h"


class Sokrat3_DB
{
public:
    Sokrat3_DB(const QString db_path);
    ~Sokrat3_DB();

    void GetListModulesName(QStringList& list) const;
    void GetListModulesDesc(QStringList& list) const;

    QStandardItemModel* GetItemModel_SokratDB();

    bool Get_DbIsOk() const;

private:
    bool CreateDB_FromFiles();
    bool ParseModuleDescFile(const QString& module_name);
    bool ParseItemModule(SModulePropertiesDesc& module_properties, const QStringList& ptrStrings_ModuleDesc, quint16& cReadStrings, quint16& numProperties);

    void CreateDB_ItemModels();
    void CreateDB_ItemTreeView();
    void LoadModuleDB_ItemTableView();


private:

    QString db_path_{};
    QString sokrat_name_{};
    QString sokrat_date_{};
    QStringList modules_names_;
    QHash<QString,QString> list_modules_desc_;
    QHash<QString,SModulePropertiesDesc> list_modules_params_;
    QHash<QString,SModulePropertiesDesc> list_modules_commands_;
    QHash<QString,SModulePropertiesDesc> list_modules_signals_;
    QString module_name_{};
    QString module_properties_{};
    SModulePropertiesDesc module_properties_values_;

    QStandardItemModel* SokratTree_ItemModel_;
    QStandardItem* SokratTree_RootItem_;
    QHash<QString,QStandardItemModel>* tableItem_modules_params_;
    QHash<QString,QStandardItemModel>* tableItem_modules_commands_;
    QHash<QString,QStandardItemModel>* tableItem_modules_signals_;


    bool dbIsOk_ = false;
};

#endif // SOKRAT3_DB_H
