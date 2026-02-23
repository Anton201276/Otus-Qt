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

public slots:

    void Slot_ShowDB_TreeViewModel(QStandardItemModel* rootModel);
    void Slot_ShowDB_ModuleTableModel(QStandardItemModel* propertiesModel);

signals:

    void Signal_ShowDB_TreeViewModel();
    void Signal_ShowDB_ModuleTableModel(const QString& moduleName, const EModuleFields field);

private:
    void handlerItemClick_TreeView(const QModelIndex &index);

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::View_DB_Sokrat3 *ui;

};

#endif // DIALOG_DB_SOKRAT3_H
