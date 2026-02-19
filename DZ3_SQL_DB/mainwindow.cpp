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
    qDebug() << "Path = " << db_sokrat_path_file;
//
//    QStringList list_names;
//    QStringList list_descs;
//    sokratDB.GetListModulesName(list_names);
//    sokratDB.GetListModulesDesc(list_descs);

//    QStringListModel *model_desc = new QStringListModel(list_descs);
//    QStringListModel *model_name = new QStringListModel(list_names);

//    ui->listView_desc->setModel(model_desc);
//    ui->listView_name->setModel(model_name);

    Form_DB_Sokrat3_ = new View_DB_Sokrat3(this, db_sokrat_path_file);
    qDebug() << " Пытаемся вывести новое окно ";
    Form_DB_Sokrat3_->exec();
}
