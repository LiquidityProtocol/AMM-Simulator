#include "PoolListWidgetItem.h"
#include "ui_PoolListWidgetItem.h"
#include "src/Protocols/Protocols.hpp"

PoolListWidgetItem::PoolListWidgetItem(QWidget *parent, PoolInterface *pool) :
    QWidget(parent),
    ui(new Ui::PoolListWidgetItem),
    pool_(pool)
{
    ui->setupUi(this);
    ui->label_poolName->setText(QString::fromStdString(pool_->pool_token()->name()));

    PROTOCOL curr_protocol = GetPoolType(pool_);
    std::string prot_name = PROTOCOL_NAME.at(curr_protocol);
    ui->lineEdit_protocol->setText(QString::fromStdString(prot_name));

    ui->lineEdit_poolFee->setText(QString::fromStdString(std::to_string(pool_->pool_fee())));

    for (auto token : pool_->tokens()) {
        ui->comboBox_spotPrice->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
    }


}

PoolListWidgetItem::~PoolListWidgetItem()
{
    delete ui;
}

PoolInterface *PoolListWidgetItem::pool() const
{
    return pool_;
}

void PoolListWidgetItem::on_comboBox_spotPrice_activated(int index)
{
    if (index!=-1){
    Token *input_token = qvariant_cast<Token *>(ui->comboBox_spotPrice->currentData());

    int token_count = 0;
    for (auto token : pool_->tokens()) {
        ui->tableWidget_poolInformation->insertRow(token_count);

        std::string filler = "-";

        std::string token_volume = token->name() + " volume";
        ui->tableWidget_poolInformation->verticalHeaderItem(token_count)->setText(QString::fromStdString(token_volume));

        ui->tableWidget_poolInformation->setItem(token_count, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(pool_->GetQuantity(token)))));
        ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem(QString::fromStdString(filler)));
        ui->tableWidget_poolInformation->setItem(token_count, 2, new QTableWidgetItem(QString::fromStdString(filler)));

        token_count++;

        std::string token_price = token->name() + " price";
        ui->tableWidget_poolInformation->verticalHeaderItem(token_count)->setText(QString::fromStdString(token_price));

        ui->tableWidget_poolInformation->setItem(token_count, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(pool_->GetSpotPrice(input_token, token)))));
        ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem(QString::fromStdString(filler)));
        ui->tableWidget_poolInformation->setItem(token_count, 2, new QTableWidgetItem(QString::fromStdString(filler)));

        token_count++;
    }
    }
}

