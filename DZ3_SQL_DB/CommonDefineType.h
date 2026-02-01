#ifndef COMMONDEFINETYPE_H
#define COMMONDEFINETYPE_H

#include <QString>
#include <QVector>
#include <QList>
#include <QStringList>

struct SokratSoftWareVersionDesc {
    QString software_name;
    qint8 data_base_version;
    qint8 data_base_day;
    qint8 data_base_month;
    qint8 data_base_year;
    qint8 firmware_version;
    qint8 firmware_day;
    qint8 firmware_month;
    qint8 firmware_year;
    SokratSoftWareVersionDesc(QString sw_name, qint8 db_ver, qint8 db_day, qint8 db_month, qint8 db_year, qint8 fw_ver, qint8 fw_day, qint8 fw_month, qint8 fw_year) {
        software_name = sw_name;
        data_base_version = db_ver;
        data_base_day = db_day;
        data_base_month = db_month;
        data_base_year = db_year;
        firmware_version = fw_ver;
        firmware_day = fw_day;
        firmware_month = fw_month;
        firmware_year = fw_year;
    }
};

enum class EDescDataType {
    bdtSigned = 0,
    bdtUnsigned = 1,
    bdtBin = 2
};

struct SModulePropertiesDesc {
    quint8 cProperties;
    QVector<quint32> Address;
    QStringList NameProperties;
    QVector<EDescDataType> enDBTypes;
    QVector<quint16> usBits;
    QStringList NameBits;
    QVector<quint32> InitValue;
    QVector<quint32> MinValue;
    QVector<quint32> MaxValue;
    //QVector<quint32> RealValue;
    //QVector<quint32> NewValue;
};

struct SModuleDataBase {
    QString ModuleName;
    QString ModuleDesc;
    SModulePropertiesDesc SParams;
    SModulePropertiesDesc SCommand;
    SModulePropertiesDesc SSignals;
};


#endif // COMMONDEFINETYPE_H
