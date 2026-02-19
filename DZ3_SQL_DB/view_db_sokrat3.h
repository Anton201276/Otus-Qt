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
    explicit View_DB_Sokrat3(QWidget *parent = nullptr, QString Sokrat_desc = "");
    ~View_DB_Sokrat3();

private:
    void handlerItemClick_TreeView(const QModelIndex &index);

private:
    Ui::View_DB_Sokrat3 *ui;
    Sokrat3_DB *sokratDB_;

};

#endif // DIALOG_DB_SOKRAT3_H
