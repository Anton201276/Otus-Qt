#include "view_db_sokrat3.h"
#include "ui_view_db_sokrat3.h"

View_DB_Sokrat3::View_DB_Sokrat3(QWidget *parent, QString Sokrat_desc_path) :
    QDialog(parent),
    ui(new Ui::View_DB_Sokrat3)
{
    ui->setupUi(this);

    sokratDB_ = new Sokrat3_DB(Sokrat_desc_path);

    //qDebug() << "+++ Show View_DB_Sokrat3 +++";
    ui->treeView->setModel(&sokratDB_->GetItemModel_SokratDB());

    connect(ui->treeView, &QTreeView::clicked, this, &View_DB_Sokrat3::handlerItemClick_TreeView);
}

View_DB_Sokrat3::~View_DB_Sokrat3()
{
    delete ui;
    //delete sokratDB_;
}

void View_DB_Sokrat3::handlerItemClick_TreeView(const QModelIndex &index) {

    if (!index.isValid()) return;

    QVariant userData = sokratDB_->GetItemModel_SokratDB().data(index, Qt::UserRole);

//    QString text = sokratDB_->GetItemModel_SokratDB()->data(index, Qt::DisplayRole).toString();
//        int row = index.row();
//        int col = index.column();

        if (userData.isValid()) {
            QString text_mdl = sokratDB_->GetItemModel_SokratDB().data(index, Qt::UserRole).toString();
            QString text_prop = sokratDB_->GetItemModel_SokratDB().data(index, Qt::DisplayRole).toString();
            qDebug() << "Клик на элементе: " << text_mdl << " - " << text_prop;
        }
}
