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
    db_esc_path_file_ = QFileDialog::getOpenFileName(nullptr, "Найти System.stm","", "*.stm");
    qDebug() << "Path = " << db_esc_path_file_;
}
