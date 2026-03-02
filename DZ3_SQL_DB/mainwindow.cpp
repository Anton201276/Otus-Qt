#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "view_db_sokrat3.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handlerItemClick_TreeView);
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

void MainWindow::Slot_GetDB_SokratDBModel(Sokrat3_DB* sokratDB){
    Form_DB_Sokrat3_ = new View_DB_Sokrat3(this);
    Form_DB_Sokrat3_->SetDB_SokratDB(sokratDB);
    Form_DB_Sokrat3_->exec();

    if (Form_DB_Sokrat3_->Get_SaveSokratDB()) {
        emit Signal_GiveDB_TreeViewModel();
    }
}

void MainWindow::Slot_GetDB_TreeViewModel(QStandardItemModel* rootModel) {
    treeViewModel_ = rootModel;
    ui->treeView->setModel(treeViewModel_);
}

void MainWindow::handlerItemClick_TreeView(const QModelIndex &index) {
    qDebug() << "Клик мыши на элементе row = " << index.row() << ", column = " << index.column() << "\n";
}

