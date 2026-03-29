#include "sokrat3_db.h"

Sokrat3_DB::Sokrat3_DB(const QString& db_pathname): db_pathname_(db_pathname)
{
    dbSqlIsOk_ = OpenSqliteDB();
}

bool Sokrat3_DB::OpenSqliteDB() {

    QSqlDatabase sqlDB = QSqlDatabase::addDatabase("QSQLITE");

    QDir dir;
    if (!dir.mkpath(db_pathname_)) {
        qWarning() << "Не удалось создать директорию:" << db_pathname_;
        return false;
    } else {
        qDebug() << "Директория создана или уже существует:" << db_pathname_;
    }

    QString new_path = db_pathname_ + "/Sokrat3_Dev1" + ".db";
    QFile db_file(new_path);

    if (db_file.exists()) {
        db_file.remove();
        qDebug() << "Файл SQL-базы удален: " << new_path << "\n";
    }
    else {
        qDebug() << "Файл SQL-базы создан: " << new_path << "\n";
    }

    sqlDB.setDatabaseName(new_path);

    if (!sqlDB.open()) {
        qDebug() << "Ошибка открытия БД: " << new_path << " error: " << sqlDB.lastError().text() << "\n";
        return false;
    }
    else {
        qDebug() << "Файл SQL-базы данных создан по пути: " << new_path << "\n";
    }

    dbSqlIsOk_ = createAllSqlTable(sqlDB);

    if (!dbSqlIsOk_) {
        qDebug() << "SQL таблицы не созданы" << "\n";
        return dbSqlIsOk_;
    }

    db_file_name_ = "/Sokrat3_Dev1.db";
    sqlDB_ = sqlDB;

    return true;
}

bool Sokrat3_DB::createAllSqlTable(const QSqlDatabase& sqlDB) {

    QSqlQuery query(sqlDB);

    qDebug() << "****** Начало заполнения SQL-таблиц ******* " << "\n";

    for (QString db_name : list_module_name_) {
        QString db_create = db_query_part1_ + db_name + db_query_part3_;

        qDebug() << "Создаем SQL-таблицу: " << db_name  << "\n";

        if (!query.exec(db_create)) {
            qDebug() << "Ошибка создания таблицы: " << db_name << "  error:" << query.lastError().text() << "\n";
            return false;
        }

        QSqlTableModel sqlModel(nullptr, sqlDB);
        sqlModel.setTable(db_name);
        sqlModel.setEditStrategy(QSqlTableModel::OnManualSubmit);

        if (!sqlModel.select()) {
            qDebug() << "Ошибка открытия БД через модель: " <<  db_name << "  error:" << sqlModel.lastError().text() << "\n";
            return false;
        }

        int rowDB = hash_params_desc_[db_name].size();

        qDebug() << "Открыли модель: " <<  db_name << "  размер:" << rowDB << "\n";

        for(int row = 0; row < rowDB; ++row) {
            if (!sqlModel.insertRow(sqlModel.rowCount())) {
                    qDebug() << "Ошибка вставки строки" << sqlModel.rowCount() << "\n";
                    qDebug() << "Последняя ошибка модели:" << sqlModel.lastError().text() << "\n";
                    return false;
            }

            int colq = 1;
            QModelIndex sqlIndex = sqlModel.index(row, colq++);
            sqlModel.setData(sqlIndex, hash_params_desc_[db_name][row]);

            sqlIndex = sqlModel.index(row, colq++);
            sqlModel.setData(sqlIndex, hash_params_Value_[db_name][row]);

            sqlIndex = sqlModel.index(row, colq++);
            sqlModel.setData(sqlIndex, hash_params_MinVal_[db_name][row]);

            sqlIndex = sqlModel.index(row, colq++);
            sqlModel.setData(sqlIndex, hash_params_MaxVal_[db_name][row]);

        }

        if (!sqlModel.submitAll()) {
            qDebug() << "Ошибка сохранения в БД: " <<  db_name << "  error:" << sqlModel.lastError().text() << "\n";
            return false;
        }

    }

    qDebug() << "****** SQL-таблиц успешно заполнены ******* " << "\n";

    return true;
}

const QString Sokrat3_DB::Get_DB_FileName() const {
    return db_file_name_;
}

const QString Sokrat3_DB::Get_SQLDB_Name_ByNumber(int num) const {
    if (num < list_module_name_.size()) {
        return list_module_name_[num];
    }
    return "";
}

int Sokrat3_DB::Execute_QueryDB_ByName(const QString& db_name) {
    query_record_ = QSqlQuery(sqlDB_);
    QString query_tab = "SELECT * FROM " + db_name;

    if (!query_record_.exec(query_tab)) {
        qDebug() << "Запрос к таблице " << db_name << " не выполнен:" << query_record_.lastError().text() << "\n";
        return 0;
    }

    QString name;
    int value = 0;
    int valueMin = 0;
    int valueMax = 0;

    qDebug() << "Запрос к таблице " << db_name << " выполнен успешно";

    QSqlRecord record = query_record_.record();

    int row = 1;
    while (query_record_.next()) {
       qDebug() << "******* Новая строка -- " << row++;
       name = query_record_.value(record.indexOf("Название")).toString();
       value = query_record_.value(record.indexOf("Значение")).toInt();
       valueMin = query_record_.value(record.indexOf("Минимальное")).toInt();
       valueMax = query_record_.value(record.indexOf("Максимальное")).toInt();

       qDebug() << "Название - " << name;
       qDebug() << "Значение - " << value;
       qDebug() << "Минимальное - " << valueMin;
       qDebug() << "Максимальное - " << valueMax;
    }
    row_size_ = hash_params_desc_[db_name].size();
    return row_size_;
}

QVariant Sokrat3_DB::Get_Value_ByIndex(int row, const QString& col) {
    if (row >= row_size_) {
        return "NULL";
    }

    query_record_.seek(row);
    QSqlRecord record = query_record_.record();
    return query_record_.value(record.indexOf(col));
}
