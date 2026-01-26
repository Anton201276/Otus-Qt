#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>

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
    QString db_esc_path_file_{};
};
#endif // MAINWINDOW_H
