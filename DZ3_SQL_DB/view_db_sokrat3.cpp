#include "view_db_sokrat3.h"
#include "ui_view_db_sokrat3.h"

View_DB_Sokrat3::View_DB_Sokrat3(QWidget *parent, QString Sokrat_desc_path) :
    QDialog(parent),
    ui(new Ui::View_DB_Sokrat3)
{
    ui->setupUi(this);



    //ui->treeView->setModel(SokratTree_ItemModel_);
}

View_DB_Sokrat3::~View_DB_Sokrat3()
{
    delete ui;
}
