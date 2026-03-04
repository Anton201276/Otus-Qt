#include "mainwindow.h"

#include <QApplication>

#include "control_db.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Control_DB controller_db;

    QObject::connect(&w, SIGNAL(Signal_CreateDBFromFiles(const QString&)), &controller_db, SLOT(Slot_CreateDBFromFiles(const QString&)));
    QObject::connect(&w, SIGNAL(Signal_GiveDB_TreeViewModel()), &controller_db, SLOT(Slot_GiveDB_TreeViewModel()));
    QObject::connect(&w, SIGNAL(Signal_GiveDB_TableSqlModel(const QModelIndex&)), &controller_db, SLOT(Slot_GiveDB_TableSqlModel(const QModelIndex&)));
    QObject::connect(&w, SIGNAL(Signal_OpenSQLiteDBFromFile(const QString&)), &controller_db, SLOT(Slot_OpenSQLiteDBFromFile(const QString&)));


    QObject::connect(&controller_db, SIGNAL(Signal_GetDB_TreeViewModel(QStandardItemModel*)), &w, SLOT(Slot_GetDB_TreeViewModel(QStandardItemModel*)));
    QObject::connect(&controller_db, SIGNAL(Signal_GetDB_SokratDBModel(Sokrat3_DB*)), &w, SLOT(Slot_GetDB_SokratDBModel(Sokrat3_DB*)));
    QObject::connect(&controller_db, SIGNAL(Signal_GetDB_SqlDBModel(QSqlTableModel*, DelegateMode)),
                     &w, SLOT(Slot_GetDB_SqlDBModel(QSqlTableModel*, DelegateMode)));


    return a.exec();
}
