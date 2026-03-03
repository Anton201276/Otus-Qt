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
        ret = false;
    }
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

    if (dbSqlIsOk_) {
        return  &SqlDB_TreeItemModel_;
    }
    else if (dbIsOk_) {
        return &SokratTree_ItemModel_;
    }
    else {
        return nullptr;
    }
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
            paramItem->setData(ID_Field_Params, Qt::UserRole + 1);
            moduleItem->appendRow(paramItem);
            LoadDB_ModuleItemTableView(*it, EModuleFields::PARAMS, db_mdl.hash_modules_params[*it]);
        }

        //Команды модуля
        it_item = db_mdl.hash_modules_commands.find(*it);
        if (it_item != db_mdl.hash_modules_commands.end()) {
            QStandardItem* cmdItem = new QStandardItem(String_Commands);
            cmdItem->setData(*it, Qt::UserRole);
            cmdItem->setData(ID_Field_Commands, Qt::UserRole + 1);
            moduleItem->appendRow(cmdItem);
            LoadDB_ModuleItemTableView(*it, EModuleFields::COMMANDS, db_mdl.hash_modules_commands[*it]);
        }

        //Сигналы модуля
        it_item = db_mdl.hash_modules_signals.find(*it);
        if (it_item != db_mdl.hash_modules_signals.end()) {
            QStandardItem* signalItem = new QStandardItem(String_Signals);
            signalItem->setData(*it, Qt::UserRole);
            signalItem->setData(ID_Field_Signals, Qt::UserRole + 1);
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

void Sokrat3_DB::createSQLite_SokratDB() {
    QSqlDatabase sqlDB = QSqlDatabase::addDatabase("QSQLITE");

    QDir dir(db_path_);
    QString db_path;

    if (!dir.exists("SQL")) {
        if (!dir.mkpath("SQL")) {
            qDebug() << "Не удалось создать директорию SQL/";
            return;
        }
        else {
            db_path = db_path_ + "SQL/" + sokrat_name_ + ".db";
        }
    }
    else {
        db_path = db_path_ + "SQL/" + sokrat_name_ + ".db";
    }
    sqlDB.setDatabaseName(db_path);

    if (!sqlDB.open()) {
        qDebug() << "Ошибка открытия БД" << sqlDB.lastError().text() << "\n";
    }

    bool isOk = createMainSqlTable(sqlDB);

    if (!isOk) {
        qDebug() << "Главная таблица не создана" << "\n";
        return;
    }

    isOk = copyModelToSqlTable(sqlDB, Sql_Params);
    isOk = copyModelToSqlTable(sqlDB, Sql_Commands);
    isOk = copyModelToSqlTable(sqlDB, Sql_Signals);

    dbSqlIsOk_ = isOk;
    sqlDB_ = sqlDB;
    sqlDB_TableModel_ = new QSqlTableModel(nullptr, sqlDB_);
}

bool Sokrat3_DB::copyModelToSqlTable(const QSqlDatabase& dbc, const QString& tableName) {
    QSqlQuery query(dbc);

    QHash<QString,QStandardItemModel*>::iterator it_begin;
    QHash<QString,QStandardItemModel*>::iterator it_end;

    if (tableName == Sql_Params) {
        it_begin = tableItem_modules_params_.begin();
        it_end = tableItem_modules_params_.end();
    }
    else if (tableName == Sql_Commands) {
        it_begin = tableItem_modules_commands_.begin();
        it_end = tableItem_modules_commands_.end();
    }
    else if (tableName == Sql_Signals) {
            it_begin = tableItem_modules_signals_.begin();
            it_end = tableItem_modules_signals_.end();
    }
    else {
        return false;
    }

    for (auto it = it_begin; it != it_end; ++it) {
        QString db_name = it.key() + tableName;

        QString db_part1 = "CREATE TABLE IF NOT EXISTS ";
        QString db_part2 = " ("
                           "№ INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "Имя TEXT NOT NULL, "
                           "Тип TEXT NOT NULL, "
                           "Начальное INTEGER NOT NULL, "
                           "Минимальное INTEGER NOT NULL, "
                           "Максимальное INTEGER NOT NULL, "
                           "Адрес регистра INTEGER NOT NULL"
                           ")";

        QString db_create = db_part1 + db_name + db_part2;

        if (!query.exec(db_create)) {
            qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
            return false;
        }

        QSqlTableModel sqlModel(nullptr, dbc);
        sqlModel.setTable(db_name);
        sqlModel.setEditStrategy(QSqlTableModel::OnManualSubmit);

        if (!sqlModel.select()) {
            qDebug() << "Ошибка загрузки данных:" << sqlModel.lastError().text();
            return false;
        }

        for (int row = 0; row < it.value()->rowCount(); ++row) {
            if (!sqlModel.insertRow(sqlModel.rowCount())) {
                    qDebug() << "Ошибка вставки строки" << sqlModel.rowCount();
                    qDebug() << "Последняя ошибка модели:" << sqlModel.lastError().text();
                    return false;
            }

            int colm = 0;
            int colq = 1;
            QModelIndex modelIndex = it.value()->index(row, colm++);
            QModelIndex sqlIndex = sqlModel.index(row, colq++);
            sqlModel.setData(sqlIndex, it.value()->data(modelIndex).toString());

            modelIndex = it.value()->index(row, colm++);
            sqlIndex = sqlModel.index(row, colq++);
            sqlModel.setData(sqlIndex, it.value()->data(modelIndex).toString());

            modelIndex = it.value()->index(row, colm++);
            sqlIndex = sqlModel.index(row, colq++);
            sqlModel.setData(sqlIndex, it.value()->data(modelIndex, Qt::DisplayRole).toInt());

            modelIndex = it.value()->index(row, colm++);
            sqlIndex = sqlModel.index(row, colq++);
            sqlModel.setData(sqlIndex, it.value()->data(modelIndex, Qt::DisplayRole).toInt());

            modelIndex = it.value()->index(row, colm++);
            sqlIndex = sqlModel.index(row, colq++);
            sqlModel.setData(sqlIndex, it.value()->data(modelIndex, Qt::DisplayRole).toInt());

            modelIndex = it.value()->index(row, colm++);
            sqlIndex = sqlModel.index(row, colq++);
            sqlModel.setData(sqlIndex, it.value()->data(modelIndex, Qt::DisplayRole).toInt());
        }

        if (!sqlModel.submitAll()) {
            qDebug() << "Ошибка сохранения в БД:" << sqlModel.lastError().text();
            return false;
        }
    }
    return true;
}

bool Sokrat3_DB::createMainSqlTable(const QSqlDatabase& dbc) {

    createDescSqlTable(dbc);
    createPlantUserSqlTable(dbc,sqlist_plant);
    createPlantUserSqlTable(dbc,sqlist_user);
    createSqlTreeModel(dbc);
    return true;
}

bool Sokrat3_DB::createDescSqlTable(const QSqlDatabase& dbc) {
    QSqlQuery query(dbc);
    QString db_part1 = "CREATE TABLE IF NOT EXISTS ";
    QString db_part3 = " ("
                       "Имя TEXT NOT NULL, "
                       "Дата TEXT NOT NULL, "
                       "Расположение TEXT NOT NULL, "
                       "Модули INTEGER NOT NULL, "
                       "Параметры INTEGER NOT NULL, "
                       "Команды INTEGER NOT NULL, "
                       "Сигналы INTEGER NOT NULL"
                       ")";
    QString db_part2 = "MainDescription";

    QString db_create= db_part1 + db_part2 + db_part3;
    if (!query.exec(db_create)) {
        qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
        return false;
    }

    QSqlTableModel sqlModel(nullptr, dbc);
    sqlModel.setTable(db_part2);
    sqlModel.setEditStrategy(QSqlTableModel::OnManualSubmit);

    if (!sqlModel.select()) {
        qDebug() << "Ошибка загрузки данных:" << sqlModel.lastError().text();
        return false;
    }

    if (!sqlModel.insertRow(sqlModel.rowCount())) {
            qDebug() << "Ошибка вставки строки" << sqlModel.rowCount();
            qDebug() << "Последняя ошибка модели:" << sqlModel.lastError().text();
            return false;
    }

    int col = 0;
    QModelIndex sqlIndex = sqlModel.index(0, col++);
    sqlModel.setData(sqlIndex, sokrat_name_);

    sqlIndex = sqlModel.index(0, col++);
    sqlModel.setData(sqlIndex, sokrat_date_);

    sqlIndex = sqlModel.index(0, col++);
    sqlModel.setData(sqlIndex, db_path_);

    sqlIndex = sqlModel.index(0, col++);
    sqlModel.setData(sqlIndex, modules_names_.size());

    int cProp = 0;
    for (auto itr = tableItem_modules_params_.begin(); itr != tableItem_modules_params_.end(); ++itr) {
        cProp += itr.value()->rowCount();
    }
    sqlIndex = sqlModel.index(0, col++);
    sqlModel.setData(sqlIndex, cProp);

    cProp = 0;
    for (auto itr = tableItem_modules_commands_.begin(); itr != tableItem_modules_commands_.end(); ++itr) {
        cProp += itr.value()->rowCount();
    }
    sqlIndex = sqlModel.index(0, col++);
    sqlModel.setData(sqlIndex, cProp);

    cProp = 0;
    for (auto itr = tableItem_modules_signals_.begin(); itr != tableItem_modules_signals_.end(); ++itr) {
        cProp += itr.value()->rowCount();
    }
    sqlIndex = sqlModel.index(0, col++);
    sqlModel.setData(sqlIndex, cProp);

    if (!sqlModel.submitAll()) {
        qDebug() << "Ошибка сохранения в  заводские/пользовательские таблицы БД:" << sqlModel.lastError().text();
        return false;
    }

    return true;
}

bool Sokrat3_DB::createPlantUserSqlTable(const QSqlDatabase& dbc, const QString field) {
    QSqlQuery query(dbc);
    QString db_part1 = "CREATE TABLE IF NOT EXISTS ";
    QString db_part3 = " ("
                       "№ INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "Имя TEXT NOT NULL, "
                       "Название TEXT NOT NULL, "
                       "Параметры INTEGER NOT NULL, "
                       "Команды INTEGER NOT NULL, "
                       "Сигналы INTEGER NOT NULL"
                       ")";

    QString db_part4 = " ("
                       "№ INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "Параметры INTEGER NOT NULL, "
                       "Команды INTEGER NOT NULL, "
                       "Сигналы INTEGER NOT NULL"
                       ")";

    QString db_create= db_part1 + field + db_part3;
    if (!query.exec(db_create)) {
        qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
        return false;
    }

    db_create= db_part1 + sqlDB_ModuleFieldDesc + db_part4;
    if (!query.exec(db_create)) {
        qDebug() << "Ошибка создания таблицы с полями модулей:" << query.lastError().text();
        return false;
    }

    QSqlTableModel sqlModel(nullptr, dbc);
    sqlModel.setTable(field);
    sqlModel.setEditStrategy(QSqlTableModel::OnManualSubmit);

    if (!sqlModel.select()) {
        qDebug() << "Ошибка загрузки данных:" << sqlModel.lastError().text();
        return false;
    }

    int id_start = 0;
    int id_end = 0;

    if (field == sqlist_plant) {
        id_end = CountPlantSokratModules;
    }
    else if (field == sqlist_user) {
        id_start = CountPlantSokratModules;
        id_end = modules_names_.size();
    }
    else {
        qDebug() << "Ошибка создания таблиц модулей" << "\n";
        return false;
    }

    int row = 0;
    for (int id = id_start; id < id_end; ++id) {
        if (!sqlModel.insertRow(sqlModel.rowCount())) {
                qDebug() << "Ошибка вставки строки" << sqlModel.rowCount();
                qDebug() << "Последняя ошибка модели:" << sqlModel.lastError().text();
                return false;
        }

        int colm = 1;
        QModelIndex sqlIndex = sqlModel.index(row, colm++);
        sqlModel.setData(sqlIndex, modules_names_[id]);

        sqlIndex = sqlModel.index(row, colm++);
        sqlModel.setData(sqlIndex, list_modules_desc_[modules_names_[id]]);

        sqlIndex = sqlModel.index(row, colm++);
        auto itr = tableItem_modules_params_.find(modules_names_[id]);
        if (itr != tableItem_modules_params_.end()) {
            int cProp = itr.value()->rowCount();
            sqlModel.setData(sqlIndex, cProp);
        }
        else {
            sqlModel.setData(sqlIndex, 0);
        }

        sqlIndex = sqlModel.index(row, colm++);
        itr = tableItem_modules_commands_.find(modules_names_[id]);
        if (itr != tableItem_modules_commands_.end()) {
            int cProp = itr.value()->rowCount();
            sqlModel.setData(sqlIndex, cProp);
        }
        else {
            sqlModel.setData(sqlIndex, 0);
        }

        sqlIndex = sqlModel.index(row, colm++);
        itr = tableItem_modules_signals_.find(modules_names_[id]);
        if (itr != tableItem_modules_signals_.end()) {
            int cProp = itr.value()->rowCount();
            sqlModel.setData(sqlIndex, cProp);
        }
        else {
            sqlModel.setData(sqlIndex, 0);
        }

        if (!sqlModel.submitAll()) {
            qDebug() << "Ошибка сохранения в  заводские/пользовательские таблицы БД:" << sqlModel.lastError().text();
            return false;
        }

        ++row;
    }
    return true;
}

bool Sokrat3_DB::createSqlTreeModel(const QSqlDatabase& dbc){

    QSqlQuery query(dbc);
    QString query_tab = "SELECT * FROM MainDescription";

    if (!query.exec(query_tab)) {
        qDebug() << "Запрос к таблице описания БД не выполнен" << query.lastError().text() << "\n";
        return false;
    }

    query.first();
    QSqlRecord rec = query.record();
    QString sokrat_name = query.value(rec.indexOf("Имя")).toString();

    SqlDB_TreeRootItem_.setText(sokrat_name);
    SqlDB_TreeRootItem_.setRowCount(2);

    QStandardItem* plantItem = new QStandardItem("Настройки изготовителя");
    QStandardItem* userItem = new QStandardItem("Настройки пользователя");
    SqlDB_TreeRootItem_.setChild(0,0,plantItem);
    SqlDB_TreeRootItem_.setChild(1,0,userItem);
    SqlDB_TreeItemModel_.appendRow(&SqlDB_TreeRootItem_);
    SqlDB_TreeItemModel_.setHorizontalHeaderLabels({"База данных контроллера Сократ-3"});

    addItemSqlTreeModel(dbc, plantItem, sqlist_plant);
    addItemSqlTreeModel(dbc, userItem, sqlist_user);

    return true;
}

bool Sokrat3_DB::addItemSqlTreeModel(const QSqlDatabase& dbc, QStandardItem* rootItem, QString type) {

    QSqlQuery query(dbc);
    QString query_tab = "SELECT * FROM " + type;

    if (!query.exec(query_tab)) {
        qDebug() << "Запрос к таблице заводских/пользовательских параметров не выполнен:" << query.lastError().text() << "\n";
        return false;
    }

    QString name;
    QString desc;
    int cParams = 0;
    int cCommands = 0;
    int cSignals = 0;

    QSqlRecord rec = query.record();
    while (query.next()) {
        name = query.value(rec.indexOf("Имя")).toString();
        desc = query.value(rec.indexOf("Название")).toString();
        cParams = query.value(rec.indexOf(String_Params)).toInt();
        cCommands = query.value(rec.indexOf(String_Commands)).toInt();
        cSignals = query.value(rec.indexOf(String_Signals)).toInt();

        QStandardItem* moduleItem = new QStandardItem(desc);
        moduleItem->setData(name, Qt::UserRole);

        if (cParams > 0) {
            QStandardItem* propItem = new QStandardItem(String_Params);
            //propItem->setData(name, Qt::UserRole);
            propItem->setData(ID_Field_Params, Qt::UserRole);
            moduleItem->appendRow(propItem);
        }

        if (cCommands > 0) {
            QStandardItem* propItem = new QStandardItem(String_Commands);
            //propItem->setData(name, Qt::UserRole);
            propItem->setData(ID_Field_Commands, Qt::UserRole);
            moduleItem->appendRow(propItem);
        }

        if (cSignals > 0) {
            QStandardItem* propItem = new QStandardItem(String_Signals);
            //propItem->setData(name, Qt::UserRole);
            propItem->setData(ID_Field_Signals, Qt::UserRole);
            moduleItem->appendRow(propItem);
        }

        rootItem->appendRow(moduleItem);
    }

    return true;
}

QSqlTableModel* Sokrat3_DB::GetItemModel_FromSqlDataBase(const QModelIndex& index) {

    int depth = 0;
    QModelIndex current = index;

    while (current.parent().isValid()) {
        depth++;
        current = current.parent();
    }

    if (depth == 0) {
        sqlDB_TableModel_->setTable(sqlDB_MainDesc);
        sqlDB_TableModel_->select();
        qDebug() << "Запрос к контроллеру" << "\n";
    }
    else if (depth == 1) {
        QString table;
        if (index.row() == 0) {
            table = sqlist_plant;
            qDebug() << "Запрос к таблице завода" << "\n";
        }
        else {
            table = sqlist_user;
            qDebug() << "Запрос к таблице пользователя" << "\n";
        }
        sqlDB_TableModel_->setTable(table);
        sqlDB_TableModel_->select();

    }
    else if (depth == 2) {

        QSqlQuery query(sqlDB_);
        QString query_pat1 = "SELECT * FROM ";
        QString query_pat2;
        QString query_pat3 = " WHERE Имя = :name";
        QString query_pat4;

        if (index.parent().row() == 0) {
            query_pat2 = sqlist_plant;
            qDebug() << "Запрос к таблице модуля завода - " << query_pat2 << "\n";
        }
        else {
            query_pat2 = sqlist_user;
            qDebug() << "Запрос к таблице модуля пользователя - " << query_pat2 << "\n";
        }

        query_pat4 = index.data(Qt::UserRole).toString();
        query_pat1 = query_pat1 + query_pat2 + query_pat3;

        query.prepare(query_pat1);
        query.bindValue(":name", query_pat4);

        if (!query.exec()) {
            qDebug() << "Запрос к таблице заводских/пользовательских параметров не выполнен:" << query.lastError().text() << "\n";
            qDebug() << "query_pat1: " << query_pat1 << query.lastError().text() << "\n";
            return nullptr;
        }

        QSqlRecord rec = query.record();
        query.first();
        int cParams = query.value(rec.indexOf(String_Params)).toInt();
        int cCommands = query.value(rec.indexOf(String_Commands)).toInt();
        int cSignals = query.value(rec.indexOf(String_Signals)).toInt();


        QSqlTableModel sqlModel(nullptr, sqlDB_);
        sqlModel.setTable(sqlDB_ModuleFieldDesc);
        sqlModel.setEditStrategy(QSqlTableModel::OnManualSubmit);

        if (!sqlModel.select()) {
            qDebug() << "Ошибка загрузки данных:" << sqlModel.lastError().text();
            return nullptr;
        }

        if (!sqlModel.rowCount()) {
            sqlModel.insertRow(sqlModel.rowCount());
        }

        int colm = 1;
        int row = 0;
        QModelIndex sqlIndex = sqlModel.index(row, colm++);
        sqlModel.setData(sqlIndex, cParams);

        sqlIndex = sqlModel.index(row, colm++);
        sqlModel.setData(sqlIndex, cCommands);

        sqlIndex = sqlModel.index(row, colm++);
        sqlModel.setData(sqlIndex, cSignals);

        if (!sqlModel.submitAll()) {
            qDebug() << "Ошибка сохранения в  заводские/пользовательские таблицы БД:" << sqlModel.lastError().text();
            return nullptr;
        }

        sqlDB_TableModel_->setTable(sqlDB_ModuleFieldDesc);
        sqlDB_TableModel_->select();

    }
    return sqlDB_TableModel_;
}
