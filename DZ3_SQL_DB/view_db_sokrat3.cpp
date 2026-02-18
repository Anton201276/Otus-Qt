#include "view_db_sokrat3.h"
#include "ui_view_db_sokrat3.h"

View_DB_Sokrat3::View_DB_Sokrat3(QWidget *parent, QString Sokrat_desc_path) :
    QDialog(parent),
    ui(new Ui::View_DB_Sokrat3)
{
    ui->setupUi(this);
     model_ = new QStandardItemModel(1, 1);
     //rootItem_ = model_->invisibleRootItem();
     rootItem_ = model_->item(0,0);
     rootItem_->appendRow(new QStandardItem("Корневой элемент"));



      //QStandardItem *parentItem = model_->invisibleRootItem();
      for (int i = 0; i < 4; ++i) {
          QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
          //rootItem_->appendRow(item);
          //parentItem = item;
          rootItem_->setChild(i,item);
      }
      ui->treeView->setModel(model_);
}

View_DB_Sokrat3::~View_DB_Sokrat3()
{
    delete ui;
}
