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

void View_DB_Sokrat3::SetDB_TreeViewModel(QStandardItemModel* rootModel) {
    ui->treeView->setModel(rootModel);
}

void View_DB_Sokrat3::SetDB_ModuleTableModel(QStandardItemModel* propertiesModel){
    ui->tableView->setModel(propertiesModel);
}

void View_DB_Sokrat3::handlerItemClick_TreeView(const QModelIndex &index) {

    if (!index.isValid()) return;

    qDebug() << "Клик на элементе: " << index.row() << " - " << index.column();

    //QVariant userData = sokratDB_->GetItemModel_SokratDB().data(index, Qt::UserRole);

//        if (userData.isValid()) {
//            QString text_mdl = sokratDB_->GetItemModel_SokratDB().data(index, Qt::UserRole).toString();
//            QString text_prop = sokratDB_->GetItemModel_SokratDB().data(index, Qt::DisplayRole).toString();
//            qDebug() << "Клик на элементе: " << text_mdl << " - " << text_prop;

//            if (text_prop == String_Params) {
//                ui->tableView->setModel(sokratDB_->GetItemModel_ModuleProperties(text_mdl, EModuleFields::PARAMS));
//                qDebug() << "Size row = " << sokratDB_->GetItemModel_ModuleProperties(text_mdl, EModuleFields::PARAMS)->rowCount();
//            }
//            else if (text_prop == String_Commands) {
//                ui->tableView->setModel(sokratDB_->GetItemModel_ModuleProperties(text_mdl, EModuleFields::COMMANDS));
//                qDebug() << "Size row = " << sokratDB_->GetItemModel_ModuleProperties(text_mdl, EModuleFields::PARAMS)->rowCount();
//            }
//            else {
//                ui->tableView->setModel(sokratDB_->GetItemModel_ModuleProperties(text_mdl, EModuleFields::SIGNALS));
//                qDebug() << "Size row = " << sokratDB_->GetItemModel_ModuleProperties(text_mdl, EModuleFields::PARAMS)->rowCount();
//            }
//        }
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
