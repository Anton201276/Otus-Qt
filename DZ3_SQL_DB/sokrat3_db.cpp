#include "sokrat3_db.h"

Sokrat3_DB::Sokrat3_DB(const QString db_path): db_path_(db_path){
    SModuleDataBase SDataBase;
    dbIsOk_ = CreateItemModelDB_FromFiles(SDataBase);
}

Sokrat3_DB::~Sokrat3_DB() {
    qDeleteAll(tableItem_modules_params_);  // Удаляет все QStandardItemModel* в хэше
    tableItem_modules_params_.clear();

    qDeleteAll(tableItem_modules_commands_);  // Удаляет все QStandardItemModel* в хэше
    tableItem_modules_commands_.clear();

    qDeleteAll(tableItem_modules_signals_);  // Удаляет все QStandardItemModel* в хэше
    tableItem_modules_signals_.clear();
}


bool Sokrat3_DB::CreateItemModelDB_FromFiles(SModuleDataBase& db_mdl){

    bool ret = true;
    QFile system_file(db_path_);

    if (QFile::exists(db_path_) && system_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Читаем данные
        qint16 cRead_string = 0;
        qint16 cModules = 0;
        qint16 numberStringNameModule = stringNumber_SysModulName;
        QString read_string;
        QString name_string;

        read_string = system_file.readLine();
        cRead_string++;
        sokrat_name_ = system_file.readLine();
        sokrat_name_ = sokrat_name_.trimmed();
        cRead_string++;

        read_string = system_file.readLine();
        read_string = read_string.trimmed();
        sokrat_name_ += "_v" + read_string;
        cRead_string++;

        read_string = system_file.readLine();
        cRead_string++;

        read_string = system_file.readLine();
        read_string = read_string.trimmed();
        sokrat_date_ = read_string;
        cRead_string++;

        while ((read_string = system_file.readLine()) != NULL) {
            cRead_string++;
            if (cRead_string == numberStringNameModule) {
                name_string = read_string.trimmed();
                modules_names_ << name_string;

                ret = ParseModuleDescFile(name_string, db_mdl);
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
        //qDebug() << "Ошибка открытия файла:" << system_file.errorString();
        ret = false;
    }

    //Создаем ItemData для Представлений
    CreateDB_ItemModels(db_mdl);

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

bool Sokrat3_DB::ParseModuleDescFile(const QString& name_module, SModuleDataBase& db_mdl) {
    bool ret = true;

    QString module_path = db_path_.remove("System.stm") + "Modules/" + name_module + ".mdl";
    QFile module_file(module_path);
    QTextStream text_stream(&module_file);
    text_stream.setCodec("Windows-1251");

    if (QFile::exists(module_path) && module_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        quint16 cRead_string = 0;
        QStringList allStrings_ModuleDesc;

        while(!text_stream.atEnd()) {
            allStrings_ModuleDesc << text_stream.readLine();
        }

        list_modules_desc_[name_module] = allStrings_ModuleDesc[cRead_string];

        cRead_string = stringNumber_MdlCountProperty;
        QVector<SPropertyDesc> module_properties;
        quint16 number_prop = 0;


        //Параметры модуля
        number_prop = allStrings_ModuleDesc[cRead_string].toInt();
        if (number_prop > 0) {
            ParsePropertiesModule(module_properties, allStrings_ModuleDesc, cRead_string, number_prop);
            db_mdl.hash_modules_params[name_module] = std::move(module_properties);
        }
        else {
            cRead_string++;
        }

        //Команды модуля
        number_prop = allStrings_ModuleDesc[cRead_string].toInt();
        if (number_prop > 0) {
            ParsePropertiesModule(module_properties, allStrings_ModuleDesc, cRead_string, number_prop);
            db_mdl.hash_modules_commands[name_module] = std::move(module_properties);
        }
        else {
            cRead_string++;
        }

        //Сигналы модуля
        number_prop = allStrings_ModuleDesc[cRead_string].toInt();
        if (number_prop > 0) {
            ParsePropertiesModule(module_properties, allStrings_ModuleDesc, cRead_string, number_prop);
            db_mdl.hash_modules_signals[name_module] = std::move(module_properties);
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

bool Sokrat3_DB::ParsePropertiesModule(QVector<SPropertyDesc>& module_properties, const QStringList& strings_ModuleDesc, quint16& cReadStrings, quint16& numProperties){
    bool ret = true;
    cReadStrings++;

    for(quint16 j = 0; j < numProperties; ++j) {
        SPropertyDesc tmpDesc;
        tmpDesc.Address = j + 100;
        tmpDesc.Desc = strings_ModuleDesc[cReadStrings++];
        cReadStrings++;

        if (strings_ModuleDesc[cReadStrings] == "U2" || strings_ModuleDesc[cReadStrings] == "I2") {
            tmpDesc.Bits = 0;
            tmpDesc.enDBTypes = strings_ModuleDesc[cReadStrings++] == "U2" ? EDescDataType::bdtUnsigned : EDescDataType::bdtSigned;
            tmpDesc.InitValue = (strings_ModuleDesc[cReadStrings++]).toInt();
            tmpDesc.MinValue = (strings_ModuleDesc[cReadStrings++]).toInt();
            tmpDesc.MaxValue = (strings_ModuleDesc[cReadStrings++]).toInt();
            cReadStrings++;
        }
        else {
            tmpDesc.enDBTypes = EDescDataType::bdtBin;
            tmpDesc.InitValue = (strings_ModuleDesc[++cReadStrings]).toUInt();
            tmpDesc.MinValue = 0;
            tmpDesc.MaxValue = 65535;
            quint16 numBits = (strings_ModuleDesc[++cReadStrings]).toUInt();
            tmpDesc.Bits = numBits;
            cReadStrings += 2;
            for (quint16 j = 0; j < numBits; ++j) {
                tmpDesc.NameBits << strings_ModuleDesc[cReadStrings];
                cReadStrings += 2;
            }
        }
        module_properties.push_back(std::move(tmpDesc));
    }
    return ret;
}

void Sokrat3_DB::CreateDB_ItemModels(const SModuleDataBase& db_mdl) {

    SokratTree_RootItem_.setText(sokrat_name_);
    SokratTree_RootItem_.setRowCount(2);

    CreateDB_ItemTreeView(db_mdl);

    return;
}

QStandardItemModel* Sokrat3_DB::GetItemModel_SokratDB() {
    return &SokratTree_ItemModel_;
}

void Sokrat3_DB::CreateDB_ItemTreeView(const SModuleDataBase& db_mdl) {

    QStandardItem* plantItem = new QStandardItem("Настройки изготовителя");
    QStandardItem* userItem = new QStandardItem("Настройки пользователя");
    SokratTree_RootItem_.setChild(0,0,plantItem);
    SokratTree_RootItem_.setChild(1,0,userItem);
    SokratTree_ItemModel_.appendRow(&SokratTree_RootItem_);
    SokratTree_ItemModel_.setHorizontalHeaderLabels({"База данных контроллера Сократ-3"});

    for (auto it = modules_names_.begin(); it != modules_names_.end(); ++it) {
        QStandardItem* moduleItem = new QStandardItem(list_modules_desc_[*it]);

        //Параметры модуля
        auto it_item = db_mdl.hash_modules_params.find(*it);
        if (it_item != db_mdl.hash_modules_params.end()) {
            QStandardItem* paramItem = new QStandardItem(String_Params);
            paramItem->setData(*it, Qt::UserRole);
            moduleItem->appendRow(paramItem);
            LoadDB_ModuleItemTableView(*it, EModuleFields::PARAMS, db_mdl.hash_modules_params[*it]);
        }

        //Команды модуля
        it_item = db_mdl.hash_modules_commands.find(*it);
        if (it_item != db_mdl.hash_modules_commands.end()) {
            QStandardItem* cmdItem = new QStandardItem(String_Commands);
            cmdItem->setData(*it,Qt::UserRole);
            moduleItem->appendRow(cmdItem);
            LoadDB_ModuleItemTableView(*it, EModuleFields::COMMANDS, db_mdl.hash_modules_commands[*it]);
        }

        //Сигналы модуля
        it_item = db_mdl.hash_modules_signals.find(*it);
        if (it_item != db_mdl.hash_modules_signals.end()) {
            QStandardItem* signalItem = new QStandardItem(String_Signals);
            signalItem->setData(*it,Qt::UserRole);
            moduleItem->appendRow(signalItem);
            LoadDB_ModuleItemTableView(*it, EModuleFields::SIGNALS,  db_mdl.hash_modules_signals[*it]);
        }

        if (it < modules_names_.begin() + CountPlantSokratModules) {
            plantItem->appendRow(moduleItem);
        }
        else {
            userItem->appendRow(moduleItem);
        }
    }
}

void Sokrat3_DB::LoadDB_ModuleItemTableView(const QString& mdl, EModuleFields field, const QVector<SPropertyDesc>& mdl_prop){

    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(Count_Column_Table);
    model->setHorizontalHeaderLabels({"Имя", "Тип", "Начальное", "Минимальное", "Максимальное", "Адрес регистра"});

    for (int row = 0; row < mdl_prop.size(); ++row) {
        QList<QStandardItem*> rowProprties = LoadDB_RowProperties(mdl_prop[row]);
        model->appendRow(rowProprties);
    }

    if (field == EModuleFields::PARAMS) {
        tableItem_modules_params_.insert(mdl, model);
    }
    else if (field == EModuleFields::COMMANDS) {
        tableItem_modules_commands_.insert(mdl, model);
    }
    else {
        tableItem_modules_signals_.insert(mdl, model);
    }
}

QList<QStandardItem*> Sokrat3_DB::LoadDB_RowProperties(const SPropertyDesc& sprop) {
    QList<QStandardItem*> rowList;

    QStandardItem* item_desc = new QStandardItem(sprop.Desc);
    rowList << item_desc;

    QString datatype;
    if (sprop.enDBTypes == EDescDataType::bdtBin) {
        datatype = "Bits";
    }
    else if (sprop.enDBTypes == EDescDataType::bdtSigned) {
        datatype = "Int";
    }
    else {
        datatype = "UInt";
    }

    QStandardItem* item_DBType = new QStandardItem(datatype);
    rowList << item_DBType;

    QStandardItem* item_init = new QStandardItem();
    if (sprop.enDBTypes == EDescDataType::bdtBin) {
        item_init->setData(sprop.NameBits, Qt::ToolTipRole);
    }
    item_init->setData(sprop.InitValue, Qt::DisplayRole);
    rowList << item_init;

    QStandardItem* item_min = new QStandardItem();
    item_min->setData(sprop.MinValue, Qt::DisplayRole);
    rowList << item_min;

    QStandardItem* item_max = new QStandardItem();
    item_max->setData(sprop.MaxValue, Qt::DisplayRole);
    rowList << item_max;

    QStandardItem* item_adr = new QStandardItem();
    item_adr->setData(sprop.Address, Qt::DisplayRole);
    rowList << item_adr;

    return rowList;
}

QStandardItemModel* Sokrat3_DB::GetItemModel_ModuleProperties(const QString& mdl, EModuleFields prop) {
    QStandardItemModel* ret = nullptr;

    if (prop == EModuleFields::PARAMS) {
        ret = tableItem_modules_params_.find(mdl) != tableItem_modules_params_.end() ? tableItem_modules_params_[mdl] : nullptr;
    }
    else if (prop == EModuleFields::COMMANDS) {
        ret = tableItem_modules_commands_.find(mdl) != tableItem_modules_commands_.end() ? tableItem_modules_commands_[mdl] : nullptr;
    }
    else {
        ret = tableItem_modules_signals_.find(mdl) != tableItem_modules_signals_.end() ? tableItem_modules_signals_[mdl] : nullptr;
    }

    return ret;
}
