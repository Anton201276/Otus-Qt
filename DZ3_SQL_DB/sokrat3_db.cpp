#include "sokrat3_db.h"

Sokrat3_DB::Sokrat3_DB(const QString db_path):
    db_path_(db_path){
    dbIsOk_ = CreateDB_FromFiles();

    if (dbIsOk_) {
        qDebug() << " Create ItemModel Data Base ";
        dbItemOk = CreateDB_ItemModels();
    }
}

Sokrat3_DB::~Sokrat3_DB() {
    delete SokratTree_ItemModel_;
    delete SokratTree_RootItem_;
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
        system_file.close();
    }
    else {
        qDebug() << "Ошибка открытия файла:" << system_file.errorString();
        ret = false;
    }
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
        quint16 cRead_string = num_string_module_name;
        //QString read_string;
        QStringList allStrings_ModuleDesc;

        while(!text_stream.atEnd()) {
            allStrings_ModuleDesc << text_stream.readLine();
        }

        list_modules_desc_[name_module] = allStrings_ModuleDesc[cRead_string];
        //read_string = read_string.trimmed();
        qDebug() << "Название модуля = " << list_modules_desc_[name_module];
        //cRead_string++;

        cRead_string = num_string_module_paramas;
        SModulePropertiesDesc module_properties;
        quint16 number_prop = 0;


        //Параметры модуля
        number_prop = allStrings_ModuleDesc[cRead_string].toInt();
        if (number_prop > 0) {
            ParseItemModule(module_properties, allStrings_ModuleDesc, cRead_string, number_prop);
            list_modules_params_[name_module] = std::move(module_properties);
            qDebug() << "Считали параметры";
        }
        else {
            cRead_string++;
        }

        //Команды модуля
        number_prop = allStrings_ModuleDesc[cRead_string].toInt();
        if (number_prop > 0) {
            ParseItemModule(module_properties, allStrings_ModuleDesc, cRead_string, number_prop);
            list_modules_commands_[name_module] = std::move(module_properties);
            qDebug() << "Считали команды";
        }
        else {
            cRead_string++;
        }

        //Сигналы модуля
        number_prop = allStrings_ModuleDesc[cRead_string].toInt();
        if (number_prop > 0) {
            ParseItemModule(module_properties, allStrings_ModuleDesc, cRead_string, number_prop);
            list_modules_signals_[name_module] = std::move(module_properties);
            qDebug() << "Считали сигналы";
        }
        else {
            cRead_string++;
        }

        module_file.close();
    }
    else {
        ret = false;
    }

    return ret;
}

//bool ParseItemModule(SModulePropertiesDesc& module_properties, const QStringList* ptrStrings_ModuleDesc, quint16& cReadStrings, quint16& numProperties);

bool Sokrat3_DB::ParseItemModule(SModulePropertiesDesc& module_properties, const QStringList& strings_ModuleDesc, quint16& cReadStrings, quint16& numProperties) {
    bool ret = true;
    module_properties.cProperties = numProperties;
    qDebug() << "Количество свойст элемента - " << module_properties.cProperties;
    quint16 cnt_strings  = cReadStrings + 1;

    for(quint16 j = 0; j < numProperties; ++j) {
        qDebug() << "Номер строки - " << cnt_strings;
        module_properties.Address.push_back(j);
        module_properties.NameProperties << strings_ModuleDesc[cnt_strings++];
        cnt_strings++;
        qDebug() << "Описание свойста элемента - " << module_properties.NameProperties;

        if (strings_ModuleDesc[cnt_strings] == "U2" || strings_ModuleDesc[cnt_strings] == "I2") {
            module_properties.usBits.push_back(0);
            module_properties.enDBTypes.push_back(strings_ModuleDesc[++cnt_strings] == "U2" ? EDescDataType::bdtUnsigned : EDescDataType::bdtSigned);
            module_properties.InitValue.push_back((strings_ModuleDesc[++cnt_strings]).toInt());
            module_properties.MinValue.push_back((strings_ModuleDesc[++cnt_strings]).toInt());
            module_properties.MaxValue.push_back((strings_ModuleDesc[++cnt_strings]).toInt());
            cnt_strings++;
        }
        else {
            qDebug() << "Номер строки и значение битового поля - " << cnt_strings << " ---- " << strings_ModuleDesc[cnt_strings];
            module_properties.enDBTypes.push_back(EDescDataType::bdtBin);
            module_properties.InitValue.push_back((strings_ModuleDesc[++cnt_strings]).toUInt());
            module_properties.MinValue.push_back(0);
            module_properties.MaxValue.push_back(65535);
            quint16 numBits = (strings_ModuleDesc[++cnt_strings]).toUInt();
            module_properties.usBits.push_back(numBits);
            qDebug() << "Количество бит поля = " << numBits;
            cnt_strings += 2;
            for (quint16 j = 0; j < numBits; ++j) {

                module_properties.NameBits << strings_ModuleDesc[cnt_strings];
                qDebug() << "название бита = " << module_properties.NameBits;
                qDebug() << "номер строки = " << cnt_strings;
                cnt_strings += 2;
            }
        }
    }

    cReadStrings = cnt_strings;

    return ret;
}

bool Sokrat3_DB::CreateDB_ItemModels() {
    bool ret = true;
    SokratTree_ItemModel_ = new QStandardItemModel();
    SokratTree_RootItem_ = new QStandardItem(sokrat_name_);
    SokratTree_RootItem_->setRowCount(2);
    QStandardItem* plantItem = new QStandardItem("Параметры изготовителя");
    QStandardItem* userItem = new QStandardItem("Параметры пользователя");
    SokratTree_RootItem_->setChild(0,0,plantItem);
    SokratTree_RootItem_->setChild(1,0,userItem);
    SokratTree_ItemModel_->appendRow(SokratTree_RootItem_);
    SokratTree_ItemModel_->setHorizontalHeaderLabels({"База данных контроллера Сократ-3"});

    qDebug() << " Start load dataItems ";

    for (auto it = modules_names_.begin(); it != modules_names_.end(); ++it) {
        QStandardItem* moduleItem = new QStandardItem(list_modules_desc_[*it]);
        qDebug() << " Имя модуля - " << *it;

        //Параметры модуля
        auto it_item = list_modules_params_.find(*it);
        if (it_item != list_modules_params_.end()) {
            QStandardItem* paramItem = new QStandardItem("Параметры");
            moduleItem->appendRow(paramItem);
            qDebug() << " Load params module " << *it;
        }

        //Команды модуля
        it_item = list_modules_commands_.find(*it);
        if (it_item != list_modules_commands_.end()) {
            QStandardItem* cmdItem = new QStandardItem("Команды");
            moduleItem->appendRow(cmdItem);
            qDebug() << " Load commands module " << *it;
        }

        //Сигналы модуля
        it_item = list_modules_signals_.find(*it);
        if (it_item != list_modules_signals_.end()) {
            QStandardItem* sglItem = new QStandardItem("Сигналы");
            moduleItem->appendRow(sglItem);
            qDebug() << " Load signals module " << *it;
        }

        if (it < modules_names_.begin() + CountPlantSokratModules) {
            plantItem->appendRow(moduleItem);
        }
        else {
            userItem->appendRow(moduleItem);
        }
    }
    qDebug() << " Create finish Items Module ";
    return ret;
}

QStandardItemModel* Sokrat3_DB::GetItemModel_SokratDB() {
    return SokratTree_ItemModel_;
}

/*


 */
