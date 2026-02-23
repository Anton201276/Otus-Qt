#ifndef COMMONDEFINETYPE_H
#define COMMONDEFINETYPE_H

#include <QString>
#include <QVector>
#include <QList>
#include <QHash>
#include <QStringList>
#include <QtGlobal>

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

enum class EModuleFields {
    PARAMS,
    COMMANDS,
    SIGNALS
};

struct SModulePropertiesDesc {
    quint8 cProperties;
    QStringList NameProperties;
    QVector<EDescDataType> enDBTypes;
    QVector<quint16> usBits;
    QStringList NameBits;
    QVector<qint32> InitValue;
    QVector<qint32> MinValue;
    QVector<qint32> MaxValue;
	QVector<quint32> Address;
};

inline constexpr quint8 ID_Prop_Desc = 0;
inline constexpr quint8 ID_Prop_enDBTypes = 1;
inline constexpr quint8 ID_Prop_Bits = 2;
inline constexpr quint8 ID_Prop_NameBits = 3;
inline constexpr quint8 ID_Prop_InitValue = 4;
inline constexpr quint8 ID_Prop_MinValue = 5;
inline constexpr quint8 ID_Prop_MaxValue = 6;
inline constexpr quint8 ID_Prop_Address = 7;

struct SPropertyDesc {
    QString Desc;
    EDescDataType enDBTypes;
    quint16 Bits;
    QStringList NameBits;
    qint32 InitValue;
    qint32 MinValue;
    qint32 MaxValue;
    quint32 Address;
};

struct SModuleDataBase {
    QHash<QString,QVector<SPropertyDesc>> hash_modules_params;
    QHash<QString,QVector<SPropertyDesc>> hash_modules_commands;
    QHash<QString,QVector<SPropertyDesc>> hash_modules_signals;
};

inline constexpr int CountPlantSokratModules = 9;
inline constexpr int stringNumber_SysModulName = 9;
inline constexpr int stringNumber_MdlCountProperty = 4;
inline constexpr int Count_Column_Table = 6;

inline const QString String_Params = "Параметры";
inline const QString String_Commands = "Команды";
inline const QString String_Signals = "Сигналы";

//struct SModuleRowPropertiesDesc {
//    QString NameProperties;
//    EDescDataType enDBTypes;
//    qint32 InitValue;
//    qint32 MinValue;
//    qint32 MaxValue;
//    quint32 Address;
//};


#endif // COMMONDEFINETYPE_H
