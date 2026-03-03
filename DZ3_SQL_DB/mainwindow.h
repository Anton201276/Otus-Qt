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

public slots:
    void Slot_GetDB_TreeViewModel(QStandardItemModel* rootModel);
    //void Slot_GetDB_ModuleTableModel(QStandardItemModel* propertiesModel);
    void Slot_GetDB_SokratDBModel(Sokrat3_DB* sokratDB);
    void Slot_GetDB_SqlDBModel(QSqlTableModel* sqlDBTable);

signals:
    void Signal_CreateDBFromFiles(const QString& path);
    void Signal_OpenSQLiteDBFromFile(const QString& path);
    void Signal_GiveDB_TreeViewModel();
    void Signal_GiveDB_TableSqlModel(const QModelIndex& index);

    //void Signal_ShowDB_TreeViewModel(QStandardItemModel* rootModel);
    //void Signal_ShowDB_ModuleTableModel(QStandardItemModel* propertiesModel);

private slots:
    void on_action_exit_app_triggered();
    void on_action_ESC_Config_triggered();

    void on_action_open_DB_SQL_triggered();

private:
    void handlerItemClick_TreeView(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    View_DB_Sokrat3* Form_DB_Sokrat3_;
    QStandardItemModel* treeViewModel_;

};
#endif // MAINWINDOW_H
