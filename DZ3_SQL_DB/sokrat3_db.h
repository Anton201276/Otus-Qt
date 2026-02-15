#ifndef SOKRAT3_DB_H
#define SOKRAT3_DB_H

#include <QDebug>
#include <QString>
#include <QFile>
#include <QHash>

#include "CommonDefineType.h"


class Sokrat3_DB
{
public:
    Sokrat3_DB(const QString db_path);

    void GetListModulesName(QStringList& list) const;
    void GetListModulesDesc(QStringList& list) const;

    bool Get_DbIsOk() const;

private:
    bool CreateDB_FromFiles();
    bool ParseModuleDescFile(const QString& module_name);
    //bool AddModuleProperties(QHash<QString,SModulePropertiesDesc>* ptrPropertyField, QStringList* ptrStrings_ModuleDesc, quint16 cReadStrings, quint16 numProperties);
    //bool AddModuleParameters(const QString& module_name, const QStringList* ptrStrings_ModuleDesc, quint16& cReadStrings, quint16& numProperties);
    bool ParseItemModule(SModulePropertiesDesc& module_properties, const QStringList& ptrStrings_ModuleDesc, quint16& cReadStrings, quint16& numProperties);

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
    bool dbIsOk_ = false;
};

#endif // SOKRAT3_DB_H
