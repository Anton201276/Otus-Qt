#include "sokrat3_db.h"

Sokrat3_DB::Sokrat3_DB(const QString& db_pathname): db_pathname_(db_pathname)
{
    dbSqlIsOk_ = OpenSqliteDB();
}

bool Sokrat3_DB::OpenSqliteDB() {

    QSqlDatabase sqlDB = QSqlDatabase::addDatabase("QSQLITE");
    QDir dir(db_pathname_);
    QString new_parh;

    if (!dir.exists("SQL")) {
        if (!dir.mkpath("SQL")) {
            qDebug() << "Не удалось создать директорию SQL/";
            return false;
        }
        else {
            new_parh = db_pathname_ + "SQL/" + "Sokrat3_Dev1" + ".db";
        }
    }
    else {
        new_parh = db_pathname_ + "SQL/" + "Sokrat3_Dev1" + ".db";
        QFile db_file(new_parh);
        QFileInfo fileInfo(new_parh);
        if (db_file.exists()) {
            db_file.remove();
        }
    }
    sqlDB.setDatabaseName(new_parh);

    if (!sqlDB.open()) {
        qDebug() << "Ошибка открытия БД" << sqlDB.lastError().text() << "\n";
    }

    dbSqlIsOk_ = createAllSqlTable(sqlDB);

    if (!dbSqlIsOk_) {
        qDebug() << "SQL таблицы не созданы" << "\n";
        return dbSqlIsOk_;
    }

    sqlDB_ = sqlDB;

    return true;
}

bool Sokrat3_DB::createAllSqlTable(const QSqlDatabase& sqlDB) {

    dbSqlIsOk_ = createPlantParamsTable(sqlDB);
    if (!dbSqlIsOk_) {
        qDebug() << "Таблица заводских параметров не создана" << "\n";
        return dbSqlIsOk_;
    }

    dbSqlIsOk_ = createUserParamsTable(sqlDB);
    if (!dbSqlIsOk_) {
        qDebug() << "Таблица пользовательских параметров не создана" << "\n";
        return dbSqlIsOk_;
    }

    dbSqlIsOk_ = createBlockSignalsTable(sqlDB);
    if (!dbSqlIsOk_) {
        qDebug() << "Таблица пользовательских параметров не создана" << "\n";
        return dbSqlIsOk_;
    }

    return dbSqlIsOk_;

}

bool Sokrat3_DB::createPlantParamsTable(const QSqlDatabase& sqlDB) {

    QSqlQuery query(sqlDB);
    QString db_create = db_query_part1_ + db_query_part2_params_block_ + db_query_part3_;

    if (!query.exec(db_create)) {
        qDebug() << "Ошибка создания таблицы: " << db_create << " error: " << query.lastError().text() << "\n";
        return false;
    }

    QSqlTableModel sqlModel(nullptr, sqlDB);
    sqlModel.setTable(db_query_part2_params_block_);
    sqlModel.setEditStrategy(QSqlTableModel::OnManualSubmit);

    if (!sqlModel.select()) {
        qDebug() << "Ошибка загрузки данных:" << sqlModel.lastError().text();
        return false;
    }

    for (int row = 0; row < vecParamsNamesBlock_.size(); ++row) {
        if (!sqlModel.insertRow(sqlModel.rowCount())) {
                qDebug() << "Ошибка вставки строки" << sqlModel.rowCount();
                qDebug() << "Последняя ошибка модели:" << sqlModel.lastError().text() << "\n";
                return false;
        }

        int colm = 1;
        QModelIndex sqlIndex = sqlModel.index(row, colm++);
        sqlModel.setData(sqlIndex, vecParamsNamesBlock_[row]);

        sqlIndex = sqlModel.index(row, colm++);
        sqlModel.setData(sqlIndex, vecParamsValuesBlock_[row]);

        sqlIndex = sqlModel.index(row, colm++);
        sqlModel.setData(sqlIndex, vecParamsMinValBlock_[row]);

        sqlIndex = sqlModel.index(row, colm++);
        sqlModel.setData(sqlIndex, vecParamsMaxValBlock_[row]);

    }

    if (!sqlModel.submitAll()) {
        qDebug() << "Ошибка сохранения в БД параметры блока:" << sqlModel.lastError().text() << "\n";
        return false;
    }
    else {
        qDebug() << "Успешно сохранена БД параметры блока: " << sqlModel.lastError().text() << "\n";
    }


    const QVector<QString> vecParamsNamesDrive_ = {"Тип", "Мощность ЭД", "Скорость ЭД", "Ток фазы ЭД", "Момент ЭП", "Скорость ЭП"};
    const QVector<int> vecParamsValuesDrive_ = {1, 550, 1470, 11, 1000, 100};
    const QVector<int> vecParamsMinValDrive_ = {1, 250, 1400, 10, 100, 5};
    const QVector<int> vecParamsMaxValDrive_ = {3, 7500, 2900, 150, 32000, 25};



    return true;
}

bool Sokrat3_DB::createUserParamsTable(const QSqlDatabase& sqlDB) {

    return true;
}

bool Sokrat3_DB::createBlockSignalsTable(const QSqlDatabase& sqlDB) {

    return true;
}
