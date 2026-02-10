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
    void Slot_GetPathSystemFile(QString path);
    void Slot_GetModuleNameField(QString moduleName, EModuleFields field);

signals:
    void Signal_RootItemModel(QStandardItem* rootModel);
    void Signal_PropertiesItemModel(QStandardItem* propertiesModel);

private:
    Sokrat3_DB* mySokratDB_;
    QStandardItem* rootModel_;
    QStandardItem* modulePropertiesModel_;
};

#endif // CONTROL_DB_H
