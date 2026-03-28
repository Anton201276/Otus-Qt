#ifndef SOKRAT3_DB_H
#define SOKRAT3_DB_H

#include <QtSql>
#include <QSqlDatabase>
#include <QHash>
#include <QVector>

class Sokrat3_DB
{
    //QHash<QString,QString> list_modules_desc_;
    //QHash<QString,QVector<int>> list_modules_plantParams_;
    //QHash<QString,QVector<int>> list_modules_userParams_;
    //QHash<QString,QVector<int>> list_modules_signals_;

    const QString db_query_part1_ = "CREATE TABLE IF NOT EXISTS ";
    const QString db_query_part2_ = "Sokrat3_Desc";
    const QString db_query_part3_ = " ("
                       "№ INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "Название TEXT NOT NULL, "
                       "Значение INTEGER NOT NULL, "
                       "Минимальное INTEGER NOT NULL, "
                       "Максимальное INTEGER NOT NULL, "
                       ")";

    const QVector<QString> module_name_ = {"mdlParamsBlock", "mdlParamsDrive", "mdlParamsDefence", "mdlParamsTorque", "mdlParamsValve", "mdlParamsControl", "mdlBlockSignals"};
    const QHash<QString,QString> list_modules_desc_ = {{"mdlParamsBlock", "Парам блок"},
                                                 {"mdlParamsDrive", "Парам привода"},
                                                 {"mdlParamsDefence", "Парам защит"},
                                                 {"mdlParamsTorque", "Парам момент"},
                                                 {"mdlParamsValve", "Парам движен"},
                                                 {"mdlParamsControl", "Парам управл"},
                                                 {"mdlBlockSignals", "Сигналы блока"}
                                                };



    const QHash<QString,QVector<QString>> hash_params_desc_ = {
        {"mdlParamsBlock", {"Блок №", "Число", "Месяц", "Год", "Тип"}},
        {"mdlParamsDrive", {"Тип", "Мощность ЭД", "Скорость ЭД", "Ток фазы ЭД", "Момент ЭП", "Скорость ЭП"}},
        {"mdlParamsDefence", {"Напр мин", "Напр макс", "Ток %мин", "Ток %макс", "Темпр мин", "Темпр макс"}},
        {"mdlParamsTorque", {"Зона МВЗ", "Зона МВО", "Момент МВЗ", "Момент МВО", "Момент МВП", "Время МВ"}},
        {"mdlParamsValve", {"Реверс", "Зона управ", "Зона КВЗ", "Зона КВО"}},
        {"mdlParamsControl", {"Ист ДУ", "Функц Вход4", "Стоп МПУ", "Цикл", "Время КВО", "Время КВЗ"}},
        {"mdlBlockSignals", {"Регистр Стс", "Пололжение %", "Момент %", "Момент Нм", "Регистр Аварий", "Температура"}}
    };

    const QHash<QString,QVector<int>> hash_params_Value_ = {
        {"mdlParamsBlock", {301, 20, 12, 2015, 3}},
        {"mdlParamsDrive", {1, 550, 1470, 11, 1000, 100}},
        {"mdlParamsDefence", {170, 250, 50, 120, -25, 70}},
        {"mdlParamsTorque", {250, 250, 25, 25, 25, 20}},
        {"mdlParamsValve", {250, 250, 25, 25}},
        {"mdlParamsControl", {3, 0, 1, 0, 5, 5}},
        {"mdlBlockSignals", {0, 0, 0, 0, 0, 25}}
    };

    const QHash<QString,QVector<int>> hash_params_MinVal_ = {
        {"mdlParamsBlock", {1, 1, 1, 2015, 1}},
        {"mdlParamsDrive", {1, 250, 1400, 10, 100, 5}},
        {"mdlParamsDefence", {150, 230, 40, 110, -40, 50}},
        {"mdlParamsTorque", {50, 50, 10, 10, 10, 5}},
        {"mdlParamsValve", {50, 50, 10, 10}},
        {"mdlParamsControl", {2, 0, 0, 0, 5, 5}},
        {"mdlBlockSignals", {0, 0, 0, 0, 0, 0}}
    };

    const QHash<QString,QVector<int>> hash_params_MaxVal_ = {
        {"mdlParamsBlock", {15000, 31, 12, 2035, 9}},
        {"mdlParamsDrive", {3, 7500, 2900, 150, 32000, 25}},
        {"mdlParamsDefence", {190, 270, 70, 200, -10, 65}},
        {"mdlParamsTorque", {400, 400, 100, 100, 100, 50}},
        {"mdlParamsValve", {400, 400, 100, 100}},
        {"mdlParamsControl", {5, 9, 1, 3, 3600, 3600}},
        {"mdlBlockSignals", {65535, 1000, 2000, 32000, 65353, 150}}
    };

    QString db_pathname_;
    bool dbSqlIsOk_ = false;
    QSqlDatabase sqlDB_;

public:
    Sokrat3_DB(const QString& db_pathname);

private:
    bool OpenSqliteDB();
    bool createAllSqlTable(const QSqlDatabase& sqlDB);
    bool createPlantParamsTable(const QSqlDatabase& sqlDB);
    bool createUserParamsTable(const QSqlDatabase& sqlDB);
    bool createBlockSignalsTable(const QSqlDatabase& sqlDB);

};

#endif // SOKRAT3_DB_H

//    const QString db_query_part2_params_block_ = "Парам блок";
//    const QString db_query_part2_params_drive_ = "";

//    const QString db_query_part2_params_defence_ = "";
//    const QString db_query_part2_params_control_ = "Парам реле";
//    const QString db_query_part2_params_torque_ = "Парам ";
//    const QString db_query_part2_params_valve_ = "Парам движен";

//    const QString db_query_part2_signals_block_ = "Сигналы блока";
