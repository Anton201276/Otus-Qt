#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "view_db_sokrat3.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_exit_app_triggered()
{
    close();
}

void MainWindow::on_action_ESC_Config_triggered()
{
    QString db_sokrat_path_file = QFileDialog::getOpenFileName(this, "Найти System.stm","", "*.stm");
    Form_DB_Sokrat3_ = new View_DB_Sokrat3(this);

    connect(this,SIGNAL(Signal_ShowDB_TreeViewModel(QStandardItemModel*)), Form_DB_Sokrat3_,SLOT(Slot_ShowDB_TreeViewModel(QStandardItemModel*)));
    connect(this,SIGNAL(Signal_ShowDB_ModuleTableModel(QStandardItemModel*)), Form_DB_Sokrat3_,SLOT(Slot_ShowDB_ModuleTableModel(QStandardItemModel*)));
    connect(Form_DB_Sokrat3_,SIGNAL(Signal_ShowDB_TreeViewModel()), this,SLOT(Slot_ShowDB_TreeViewModel()));
    connect(Form_DB_Sokrat3_,SIGNAL(Signal_ShowDB_ModuleTableModel(const QString& moduleName, const EModuleFields field)), this,SLOT(Slot_ShowDB_ModuleTableModel(const QString& moduleName, const EModuleFields field)));

    emit Signal_CreateDBFromFiles(db_sokrat_path_file);

    Form_DB_Sokrat3_->exec();
}

void MainWindow::Slot_GiveDB_TreeViewModel(QStandardItemModel* rootModel){
    emit Signal_ShowDB_TreeViewModel(rootModel);
}

void MainWindow::Slot_GiveDB_ModuleTableModel(QStandardItemModel* propertiesModel){
    emit Signal_ShowDB_ModuleTableModel(propertiesModel);
}

void MainWindow::Slot_ShowDB_TreeViewModel(){
    Signal_GiveDB_TreeViewModel();
}
void MainWindow::Slot_ShowDB_ModuleTableModel(const QString& moduleName, const EModuleFields field){
    Signal_GiveDB_ModuleTableModel(moduleName, field);
}
