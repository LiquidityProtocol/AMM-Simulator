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
    ui->comboBox_secondToken->setCurrentIndex(-1);

    ui->label_secondToken->setHidden(true);
    ui->comboBox_secondToken->setHidden(true);

    QSizePolicy sp_retain = ui->tableWidget_poolInformation->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);

    QSizePolicy sp_retain2 = ui->widgetGraph->sizePolicy();
    sp_retain2.setRetainSizeWhenHidden(true);
    ui->widgetGraph->setHidden(true);



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

void PoolListWidgetItem::TokenGraph(Token* input_token, Token* output_token) {
    double input_token_quantity = pool_->GetQuantity(input_token);
    double output_token_quantity = pool_->GetQuantity(output_token);
    ui->widgetGraph->addGraph();
    ui->widgetGraph->graph(0)->addData(input_token_quantity, output_token_quantity);
    // give the axes some labels:
    ui->widgetGraph->xAxis->setLabel(QString::fromStdString(input_token->name()));
    ui->widgetGraph->yAxis->setLabel(QString::fromStdString(output_token->name()));
    // set axes ranges, so we see all data:
    ui->widgetGraph->xAxis->setRange(0, 2*input_token_quantity);
    ui->widgetGraph->yAxis->setRange(0, 2*output_token_quantity);
    ui->widgetGraph->replot();
    ui->widgetGraph->setFixedHeight(200);
}

void PoolListWidgetItem::on_comboBox_spotPrice_activated(int index)
{
    if (index!=-1){
        int token_number = pool_->tokens().size();

        ui->tableWidget_poolInformation->clearContents();
        ui->tableWidget_poolInformation->setRowCount(token_number*2);
        Token *input_token = qvariant_cast<Token *>(ui->comboBox_spotPrice->currentData());

        ui->comboBox_secondToken->clear();
        ui->comboBox_secondToken->setCurrentIndex(-1);
        ui->label_secondToken->setHidden(false);
        ui->comboBox_secondToken->setHidden(false);

        for (auto token : pool_->tokens()) {
            if (token!=input_token)
            {
            ui->comboBox_secondToken->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
            }
        }

        if (last_quantities.size()>0) {
            int token_count = 0;
            for (auto token : pool_->tokens()) {

                std::string token_volume = token->name() + " volume";
                ui->tableWidget_poolInformation->setVerticalHeaderItem(token_count, new QTableWidgetItem(QString::fromStdString(token_volume)));
                double delta_volume = pool_->GetQuantity(token)-last_quantities[token];

                ui->tableWidget_poolInformation->setItem(token_count, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(pool_->GetQuantity(token)))));
                if (delta_volume>0) {
                    ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(delta_volume))));
                    ui->tableWidget_poolInformation->item(token_count, 1)->setForeground(QBrush(QColor(0, 150, 0)));
                }
                else if (delta_volume==0) {
                    ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(delta_volume))));
                    ui->tableWidget_poolInformation->item(token_count, 1)->setForeground(QBrush(QColor(180, 90, 20)));
                }
                else {
                    ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(delta_volume))));
                    ui->tableWidget_poolInformation->item(token_count, 1)->setForeground(QBrush(QColor(150, 0, 0)));
                }

                ui->tableWidget_poolInformation->setItem(token_count, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(last_quantities[token]))));

                token_count+=1;

                std::string token_price = token->name() + " price";
                ui->tableWidget_poolInformation->setVerticalHeaderItem(token_count, new QTableWidgetItem(QString::fromStdString(token_price)));
                double last_price = last_spot_prices[input_token][token];
                double delta_price = pool_->GetSpotPrice(input_token,token)-last_price;

                ui->tableWidget_poolInformation->setItem(token_count, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(pool_->GetSpotPrice(input_token, token)))));
                if (delta_price>0) {
                    ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(delta_price))));
                    ui->tableWidget_poolInformation->item(token_count, 1)->setForeground(QBrush(QColor(0, 150, 0)));
                }
                else if (delta_price==0) {
                    ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(delta_price))));
                    ui->tableWidget_poolInformation->item(token_count, 1)->setForeground(QBrush(QColor(180, 90, 20)));
                }
                else {
                    ui->tableWidget_poolInformation->setItem(token_count, 1, new QTableWidgetItem( QString::fromStdString(std::to_string(delta_price))));
                    ui->tableWidget_poolInformation->item(token_count, 1)->setForeground(QBrush(QColor(150, 0, 0)));
                }
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

        if (token_number==2) {
            ui->widgetGraph->setHidden(false);
            Token *token2;
            for (auto token : pool_->tokens()) {
                if (token!=input_token) {
                    token2 = token;
                }
            }
            TokenGraph(input_token,token2);
        }

    }
}




void PoolListWidgetItem::on_comboBox_secondToken_activated(int index)
{
    if (index!=-1 && ui->comboBox_spotPrice->currentIndex()!=-1) {
        ui->widgetGraph->setHidden(false);
        ui->widgetGraph->clearGraphs();
        Token *input_token = qvariant_cast<Token *>(ui->comboBox_spotPrice->currentData());
        Token *second_token = qvariant_cast<Token *>(ui->comboBox_secondToken->currentData());
        TokenGraph(input_token,second_token);
    }
}

int PoolListWidgetItem::get_comboBox_spotPrice_index() {
    return ui->comboBox_spotPrice->currentIndex();
}

int PoolListWidgetItem::get_comboBox_secondToken_index() {
    return ui->comboBox_secondToken->currentIndex();
}

void PoolListWidgetItem::set_comboBox_spotPrice_index(int idx) {
    ui->comboBox_spotPrice->setCurrentIndex(idx);
}

void PoolListWidgetItem::set_comboBox_secondToken_index(int idx){
        ui->comboBox_secondToken->setCurrentIndex(idx);
}

