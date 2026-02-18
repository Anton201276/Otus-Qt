#ifndef DIALOG_DB_SOKRAT3_H
#define DIALOG_DB_SOKRAT3_H

#include <QDialog>
#include <QString>
#include <QStandardItemModel>
#include <QDebug>

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
    Ui::View_DB_Sokrat3 *ui;
    QStandardItemModel *model_;
    QStandardItem *rootItem_;
};

#endif // DIALOG_DB_SOKRAT3_H
