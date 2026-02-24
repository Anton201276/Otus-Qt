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

    QObject::connect(&w, SIGNAL(Signal_CreateDBFromFiles(const QString&)), &controller_db, SLOT(Slot_CreateDBFromFiles(const QString&)));
    QObject::connect(&w, SIGNAL(Signal_GiveDB_ModuleTableModel(const QString&, const EModuleFields)), &controller_db, SLOT(Slot_GiveDB_ModuleTableModel(const QString&, const EModuleFields)));

    QObject::connect(&controller_db, SIGNAL(Signal_GetDB_TreeViewModel(QStandardItemModel*)), &w, SLOT(Slot_GetDB_TreeViewModel(QStandardItemModel*)));
    QObject::connect(&controller_db, SIGNAL(Signal_GetDB_ModuleTableModel(QStandardItemModel*)), &w, SLOT(Slot_GetDB_TreeViewModel(QStandardItemModel*)));


    return a.exec();
}
