#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QStringListModel>

#include "sokrat3_db.h"
#include "view_db_sokrat3.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_exit_app_triggered();

    void on_action_ESC_Config_triggered();

private:
    Ui::MainWindow *ui;
    //QStringListModel *modules_name_model_;
    View_DB_Sokrat3* Form_DB_Sokrat3_;

};
#endif // MAINWINDOW_H
