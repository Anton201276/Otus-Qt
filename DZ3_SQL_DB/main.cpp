#include "mainwindow.h"

#include <QApplication>

#include "control_db.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Control_DB controller_db;

    //void Signal_GetDB_TreeViewModel(QStandardItem* rootModel);
    //void Signal_GetDB_ModuleTableModel(QStandardItem* propertiesModel);

    QObject::connect(&w, SIGNAL(Signal_CreateDBFromFiles(const QString& path)), &controller_db, SLOT(Slot_CreateDBFromFiles(const QString& path)));
    QObject::connect(&w, SIGNAL(Signal_GiveDB_TreeViewModel()), &controller_db, SLOT(Slot_GiveDB_TreeViewModel()));
    QObject::connect(&w, SIGNAL(Signal_GiveDB_TreeViewModel()), &controller_db, SLOT(Slot_GiveDB_TreeViewModel()));
    QObject::connect(&controller_db, SIGNAL(Signal_GetDB_TreeViewModel(QStandardItemModel*)), &w, SLOT(Slot_GiveDB_TreeViewModel(QStandardItemModel*)));
    QObject::connect(&controller_db, SIGNAL(Signal_GetDB_ModuleTableModel(QStandardItemModel*)), &w, SLOT(Slot_GiveDB_ModuleTableModel(QStandardItemModel*)));


    return a.exec();
}
