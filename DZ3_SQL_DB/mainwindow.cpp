#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QString db_sokrat_path_file = QFileDialog::getOpenFileName(nullptr, "Найти System.stm","", "*.stm");
    qDebug() << "Path = " << db_sokrat_path_file;
    Sokrat3_DB sokratDB(db_sokrat_path_file);
    QStringList list_names;
    sokratDB.GetListModulesName(list_names);
    modules_name_model_.setStringList(list_names);
    ui->treeView->setModel(&modules_name_model_);
}
