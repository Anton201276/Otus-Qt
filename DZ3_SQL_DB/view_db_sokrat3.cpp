#include "view_db_sokrat3.h"
#include "ui_view_db_sokrat3.h"

View_DB_Sokrat3::View_DB_Sokrat3(QWidget *parent, QString Sokrat_desc_path) :
    QDialog(parent),
    ui(new Ui::View_DB_Sokrat3)
{
    ui->setupUi(this);

    sokratDB_ = new Sokrat3_DB(Sokrat_desc_path);

    qDebug() << "+++ Show View_DB_Sokrat3 +++";
    ui->treeView->setModel(sokratDB_->GetItemModel_SokratDB());
}

View_DB_Sokrat3::~View_DB_Sokrat3()
{
    delete ui;
    //delete sokratDB_;
}
