#include "sokrat3_db.h"

Sokrat3_DB::Sokrat3_DB(const QString db_path):
    db_path_(db_path){
    CreateDB_FromFiles();
}

bool Sokrat3_DB::CreateDB_FromFiles() {
    bool ret=true;
    QFile system_file(db_path_);

    if (QFile::exists(db_path_) && system_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Читаем данные
        qint16 cRead_string = 0;
        qint16 cModules = 0;
        //qint16 numberStringCountModule = 11;
        qint16 numberStringNameModule = 9;
        QString read_string;
        QString name_string;

        read_string = system_file.readLine();
        cRead_string++;
        sokrat_name_ = system_file.readLine();
        sokrat_name_ = sokrat_name_.trimmed();
        cRead_string++;
        read_string = system_file.readLine();
        read_string = read_string.trimmed();
        cRead_string++;

        sokrat_name_ += "_v" + read_string;
        qDebug() << "System name - " << sokrat_name_;

        while ((read_string = system_file.readLine()) != NULL) {
            cRead_string++;
            if (cRead_string == numberStringNameModule) {
                name_string = read_string.trimmed();
                QString module_path = db_path_.remove("System.stm") + "Modules/" + name_string;
                ret = ParseModuleDescFile(module_path);
                if (!ret) {
                    break;
                }
                modules_names_ << name_string;
                numberStringNameModule += 3;
                cModules++;
                qDebug() << "Modules name - " << name_string;
            }
        }

        ret = true;
    }
    else {
        qDebug() << "Ошибка открытия файла:" << system_file.errorString();
        ret = false;
    }
    system_file.close();
    return ret;
}

void Sokrat3_DB::GetListModulesName(QStringList& list) const {
    list.clear();
    list << modules_names_;
}

void Sokrat3_DB::GetListModulesDesc(QStringList& list) const {
    list.clear();
    for (auto it = list_modules_desc_.begin(); it != list_modules_desc_.end(); ++it) {
        list << it.value();
    }
}

bool Sokrat3_DB::Get_DbIsOk() const {
    return dbIsOk_;
}

bool Sokrat3_DB::ParseModuleDescFile(const QString& path_module_name) {
    bool ret=true;
    qDebug() << "ParseModuleDesc desc = " << path_module_name;
    QFile module_file(path_module_name);

    if (QFile::exists(path_module_name) && module_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qint16 cRead_string = 0;
        QString read_string;
        read_string = module_file.readLine();
        qDebug() << "ParseModuleDesc desc = " << read_string;
    }





    return ret;
}

/*


 */
