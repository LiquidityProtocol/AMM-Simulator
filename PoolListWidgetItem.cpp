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

    ui->lineEdit_poolFee->setText(QString::fromStdString(std::to_string(pool_->pool_fee()*100)));

    for (auto token : pool_->tokens()) {
        ui->comboBox_spotPrice->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
    }
    ui->comboBox_spotPrice->setCurrentIndex(-1);


}

PoolListWidgetItem::~PoolListWidgetItem()
{
    delete ui;
}

PoolInterface *PoolListWidgetItem::pool() const
{
    return pool_;
}

void PoolListWidgetItem::set_last_quantities(std::unordered_map<Token *, double> input_quantities) {
    last_quantities = input_quantities;
}

void PoolListWidgetItem::set_last_spot_prices(std::unordered_map<Token *, std::unordered_map<Token *, double>> input_spots) {
    last_spot_prices = input_spots;
}

void PoolListWidgetItem::on_comboBox_spotPrice_activated(int index)
{
    if (index!=-1){
        int token_number = pool_->tokens().size();

        ui->tableWidget_poolInformation->clearContents();
        ui->tableWidget_poolInformation->setRowCount(token_number*2);
        Token *input_token = qvariant_cast<Token *>(ui->comboBox_spotPrice->currentData());

        if (last_quantities.size()>0) {
            int token_count = 0;
            for (auto token : pool_->tokens()) {

                std::string token_volume = token->name() + " volume";
                ui->tableWidget_poolInformation->setVerticalHeaderItem(token_count, new QTableWidgetItem(QString::fromStdString(token_volume)));
                double delta_volume = pool_->GetQuantity(token)-last_quantities[token];

                ui->tableWidget_poolInformation->setItem(token_count, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(pool_->GetQuantity(token)))));
                ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(delta_volume))));
                ui->tableWidget_poolInformation->setItem(token_count, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(last_quantities[token]))));

                token_count+=1;

                std::string token_price = token->name() + " price";
                ui->tableWidget_poolInformation->setVerticalHeaderItem(token_count, new QTableWidgetItem(QString::fromStdString(token_price)));
                double last_price = last_spot_prices[input_token][token];
                double delta_price = pool_->GetSpotPrice(input_token,token)-last_price;

                ui->tableWidget_poolInformation->setItem(token_count, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(pool_->GetSpotPrice(input_token, token)))));
                ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(delta_price))));
                ui->tableWidget_poolInformation->setItem(token_count, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(last_price))));

                token_count+=1;

            }
        }
        else {
            int token_count = 0;
            for (auto token : pool_->tokens()) {

                std::string token_volume = token->name() + " volume";
                ui->tableWidget_poolInformation->setVerticalHeaderItem(token_count, new QTableWidgetItem(QString::fromStdString(token_volume)));

                ui->tableWidget_poolInformation->setItem(token_count, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(pool_->GetQuantity(token)))));
                ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem("-"));
                ui->tableWidget_poolInformation->setItem(token_count, 2, new QTableWidgetItem("-"));

                token_count+=1;

                std::string token_price = token->name() + " price";
                ui->tableWidget_poolInformation->setVerticalHeaderItem(token_count, new QTableWidgetItem(QString::fromStdString(token_price)));

                ui->tableWidget_poolInformation->setItem(token_count, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(pool_->GetSpotPrice(input_token, token)))));
                ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem("-"));
                ui->tableWidget_poolInformation->setItem(token_count, 2, new QTableWidgetItem("-"));

                token_count+=1;

            }
        }
    }
}

