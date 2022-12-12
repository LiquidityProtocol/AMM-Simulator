#include "ui_MetricsTable.h"
#include "MetricsTable.h"

MetricsTable::MetricsTable(QWidget *parent, PoolInterface *pool) :
    QWidget(parent),
    ui(new Ui::MetricsTable),
    pool_(pool)
{
    ui->setupUi(this);

    //edit table to update metrics based on pool

    //edit the current values by iterating through the unordered set of tokens with pool_->tokens()
    //and then using pool_->GetQuantity(token) to get the quantity of each token
    //and pool_->GetPrice(token) to get the price of each token
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("test"));



//    for (auto token : pool_->tokens()) {

//        int row = 0;
//        ui->tableWidget->setItem(0,row,new QTableWidgetItem(QString::fromStdString(token->name())));
//        ui->tableWidget->setItem(0,row+1,new QTableWidgetItem(QString::number(pool_->GetQuantity(token))));
//        ui->tableWidget->setItem(0,row+2,new QTableWidgetItem(QString::number(token->real_value())));
//        row++;
//    }

}

MetricsTable::~MetricsTable()
{
    delete ui;
}

