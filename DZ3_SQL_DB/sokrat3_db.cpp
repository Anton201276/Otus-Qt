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
                modules_names_ << name_string;
                qDebug() << "Modules name - " << name_string;

                ret = ParseModuleDescFile(name_string);
                if (!ret) {
                    break;
                }

                numberStringNameModule += 3;
                cModules++;

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
    for (auto it = modules_names_.begin(); it != modules_names_.end(); ++it) {
        list << list_modules_desc_[*it];
    }
}

bool Sokrat3_DB::Get_DbIsOk() const {
    return dbIsOk_;
}

bool Sokrat3_DB::ParseModuleDescFile(const QString& name_module) {
    bool ret=true;
    QString module_path = db_path_.remove("System.stm") + "Modules/" + name_module + ".mdl";
    qDebug() << "ParseModuleDesc desc = " << module_path;
    QFile module_file(module_path);
    QTextStream text_stream(&module_file);
    text_stream.setCodec("Windows-1251");

    const quint16 num_string_module_name = 0;
    const quint16 num_string_module_paramas = 4;

    if (QFile::exists(module_path) && module_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qint16 cRead_string = num_string_module_name;
        QString read_string;
        QStringList allStrings_ModuleDesc;

        while(!text_stream.atEnd()) {
            allStrings_ModuleDesc << text_stream.readLine();
        }

        list_modules_desc_[name_module] = allStrings_ModuleDesc[cRead_string];
        //read_string = read_string.trimmed();
        qDebug() << "Название модуля = " << read_string;
        //cRead_string++;

        cRead_string = num_string_module_paramas;
        quint16 number_prop = 0;
        number_prop = allStrings_ModuleDesc[cRead_string].toInt();

        //Параметры модуля
        if (number_prop > 0) {
            AddModuleProperties(&list_modules_params_, &allStrings_ModuleDesc, cRead_string, number_prop);
        }
        else {
            cRead_string++;
        }


    }

    return ret;
}

bool Sokrat3_DB::AddModuleProperties(QHash<QString,SModulePropertiesDesc>* ptrPropertyField, QStringList* ptrStrings_ModuleDesc, quint16 cReadStrings, quint16 numProperties) {
    bool ret=true;

    return ret;
}

/*


 */
