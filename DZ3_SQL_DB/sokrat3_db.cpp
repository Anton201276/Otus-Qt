#include "sokrat3_db.h"

Sokrat3_DB::Sokrat3_DB(const QString db_path):
    db_path_(db_path){
    OpenParseSystemFile();
}

bool Sokrat3_DB::OpenParseSystemFile() {
    bool ret=false;
    QFile stm_file(db_path_);

    if (QFile::exists(db_path_) && stm_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Читаем данные
        qint16 cDataString = 0;
        qint16 cModules = 0;
        qint16 numberStringCountModule = 11;
        qint16 numberStringNameModule = 9;
        QString read_string;
        QString name_string;
        QTextStream txt_stream(&stm_file);

        read_string = txt_stream.readLine();
        cDataString++;
        sokrat_name_ = txt_stream.readLine();
        cDataString++;
        read_string = txt_stream.readLine();
        cDataString++;

        sokrat_name_ += "_v" + read_string;
        qDebug() << "System name - " << sokrat_name_;

        while (!txt_stream.atEnd()) {
            read_string = txt_stream.readLine();
            cDataString++;
            if (cDataString == numberStringNameModule) {
                name_string = read_string.trimmed();
                numberStringNameModule += 3;
            }
            if (cDataString == numberStringCountModule) {
                bool ok;
                qint16 num_module = read_string.toInt(&ok);
                if (ok && num_module > 0) {
                    while(num_module--) {
                        modules_names_ << name_string;
                        cModules++;
                        qDebug() << "Modules name - " << name_string;
                    }
                }
                else {
                    qDebug() << "Ошибка открытия файла. Закройте программу";
                }
                numberStringCountModule += 3;
            }
        }

        ret = true;
    }
    else {
        qDebug() << "Ошибка открытия файла:" << stm_file.errorString();
        ret = false;
    }

    return ret;
}

void Sokrat3_DB::GetListModulesName(QStringList& list) {
    list << modules_names_;
}

/*


 */
