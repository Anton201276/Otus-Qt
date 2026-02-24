#include "view_db_sokrat3.h"
#include "ui_view_db_sokrat3.h"

View_DB_Sokrat3::View_DB_Sokrat3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::View_DB_Sokrat3)
{
    ui->setupUi(this);
    connect(ui->treeView, &QTreeView::clicked, this, &View_DB_Sokrat3::handlerItemClick_TreeView);
}

View_DB_Sokrat3::~View_DB_Sokrat3()
{
    delete ui;
}

void View_DB_Sokrat3::SetDB_SokratDB(Sokrat3_DB* mySokratDB) {
    mySokratDB_ = mySokratDB;
    treeDBModel_ = mySokratDB_->GetItemModel_SokratDB();
    ui->treeView->setModel(treeDBModel_);
}

void View_DB_Sokrat3::handlerItemClick_TreeView(const QModelIndex &index) {

    if (!index.isValid()) return;

    QVariant userData = treeDBModel_->data(index, Qt::UserRole);

        if (userData.isValid()) {
            QStandardItemModel* tableDBModel;
            QString text_mdl = treeDBModel_->data(index, Qt::UserRole).toString();
            QString text_prop = treeDBModel_->data(index, Qt::DisplayRole).toString();

            if (text_prop == String_Params) {
                tableDBModel = mySokratDB_->GetItemModel_ModuleProperties(text_mdl, EModuleFields::PARAMS);
            }
            else if (text_prop == String_Commands) {
                tableDBModel = mySokratDB_->GetItemModel_ModuleProperties(text_mdl, EModuleFields::COMMANDS);
            }
            else {
                tableDBModel = mySokratDB_->GetItemModel_ModuleProperties(text_mdl, EModuleFields::SIGNALS);
            }
            ui->tableView->setModel(tableDBModel);
        }
//        else {
//            QString text_prop = sokratDB_->GetItemModel_SokratDB().data(index, Qt::DisplayRole).toString();
//            qDebug() << "Item Text = " << text_prop << "\n";
//            if (text_prop == "Команды RS-485") {
//                QStandardItemModel* model = sokratDB_->GetItemModel_ModuleProperties("ModbusCmdIn", EModuleFields::COMMANDS);
//                QModelIndex index = model->index(0, 0);
//                qDebug() << "RS485 Text = " << model->data(index) << "\n";
//                index = model->index(0, 1);
//                qDebug() << "RS485 Text = " << model->data(index) << "\n";
//                index = model->index(0, 2);
//                qDebug() << "RS485 Text = " << model->data(index, Qt::DisplayRole) << "\n";
//                index = model->index(0, 3);
//                qDebug() << "RS485 Text = " << model->data(index, Qt::DisplayRole) << "\n";
//                index = model->index(0, 4);
//                qDebug() << "RS485 Text = " << model->data(index, Qt::DisplayRole) << "\n";
//                index = model->index(0, 5);
//                qDebug() << "RS485 Text = " << model->data(index, Qt::DisplayRole) << "\n";

//                index = model->index(1, 0);
//                qDebug() << "RS485 Text = " << model->data(index) << "\n";
//                index = model->index(1, 1);
//                qDebug() << "RS485 Text = " << model->data(index) << "\n";
//                index = model->index(1, 2);
//                qDebug() << "RS485 Text = " << model->data(index, Qt::DisplayRole) << "\n";
//                index = model->index(1, 3);
//                qDebug() << "RS485 Text = " << model->data(index, Qt::DisplayRole) << "\n";
//                index = model->index(1, 4);
//                qDebug() << "RS485 Text = " << model->data(index, Qt::DisplayRole) << "\n";
//                index = model->index(1, 5);
//                qDebug() << "RS485 Text = " << model->data(index, Qt::DisplayRole) << "\n";
//            }
//        }
}
