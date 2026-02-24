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
    if (!db_sokrat_path_file.isEmpty()) {
        emit Signal_CreateDBFromFiles(db_sokrat_path_file);
    }
}

//void MainWindow::Slot_ShowDB_ModuleTableModel(const QString& moduleName, const EModuleFields field){
//    Signal_GiveDB_ModuleTableModel(moduleName, field);
//}

//void MainWindow::Slot_GetDB_TreeViewModel(QStandardItemModel* rootModel) {
//    Form_DB_Sokrat3_ = new View_DB_Sokrat3(this);
//    connect(Form_DB_Sokrat3_,SIGNAL(Signal_ShowDB_ModuleTableModel(const QString&, const EModuleFields)), this,SLOT(Slot_ShowDB_ModuleTableModel(const QString&, const EModuleFields)));
//    Form_DB_Sokrat3_->SetDB_TreeViewModel(rootModel);
//    Form_DB_Sokrat3_->exec();
//}

void MainWindow::Slot_GetDB_SokratDBModel(Sokrat3_DB* sokratDB){
    Form_DB_Sokrat3_ = new View_DB_Sokrat3(this);
    Form_DB_Sokrat3_->SetDB_SokratDB(sokratDB);
    Form_DB_Sokrat3_->exec();
}

//void MainWindow::Slot_GetDB_ModuleTableModel(QStandardItemModel* propertiesModel) {
//    Form_DB_Sokrat3_->SetDB_ModuleTableModel(propertiesModel);
//}
