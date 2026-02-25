#ifndef DIALOG_DB_SOKRAT3_H
#define DIALOG_DB_SOKRAT3_H

#include <QDialog>
#include <QString>
#include <QStandardItemModel>
#include <QDebug>

#include "sokrat3_db.h"

namespace Ui {
class View_DB_Sokrat3;
}

class View_DB_Sokrat3 : public QDialog
{
    Q_OBJECT

public:
    explicit View_DB_Sokrat3(QWidget *parent = nullptr);
    ~View_DB_Sokrat3();

    //void SetDB_TreeViewModel(QStandardItemModel* rootModel);
    //void SetDB_ModuleTableModel(QStandardItemModel* propertiesModel);
    void SetDB_SokratDB(Sokrat3_DB* mySokratDB);
    bool Get_SaveSokratDB() {
        return isSave_SokratDB;
    }

//signals:
    //void Signal_SaveSokratDB_SqlTableModel();

private slots:
    void on_buttonBox_accepted();
    //void on_buttonBox_accepted();

private:
    void handlerItemClick_TreeView(const QModelIndex &index);

private:
    Ui::View_DB_Sokrat3 *ui;
    Sokrat3_DB* mySokratDB_;
    QStandardItemModel* treeDBModel_;
    bool isSave_SokratDB = false;
};

#endif // DIALOG_DB_SOKRAT3_H
