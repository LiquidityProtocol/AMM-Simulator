#include "PoolListWidgetItem.h"
#include "ui_PoolListWidgetItem.h"
#include "src/Protocols/Protocols.hpp"

PoolListWidgetItem::PoolListWidgetItem(QWidget *parent, PoolInterface *pool, const std::unordered_map<Token *, double> &input_quantities, const std::unordered_map<Token *, std::unordered_map<Token *, double>> &input_spot_prices) :
    QWidget(parent),
    ui(new Ui::PoolListWidgetItem),
    pool_(pool),
    last_quantities_(input_quantities),
    last_spot_prices_(input_spot_prices)
{
    ui->setupUi(this);

    ui->label_poolName->setText(QString::fromStdString(pool_->pool_token()->name()));
    ui->lineEdit_protocol->setText(QString::fromStdString(PROTOCOL_NAME.at(GetPoolType(pool_))));
    ui->lineEdit_poolFee->setText(QString::fromStdString(std::to_string(pool_->pool_fee()*100)));

    for (auto token : pool_->tokens()) {
        ui->comboBox_spotPrice->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
    }

    curr_quantities_ = pool->quantities();
    for (auto input_token : pool->tokens()) {
        for (auto token : pool->tokens()) {
            curr_spot_prices_[input_token][token] = pool->GetSpotPrice(input_token, token);
        }
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

std::unordered_map<Token *, double> PoolListWidgetItem::curr_quantities() const
{
    return curr_quantities_;
}

std::unordered_map<Token *, std::unordered_map<Token *, double> > PoolListWidgetItem::curr_spot_prices() const
{
    return curr_spot_prices_;
}

int PoolListWidgetItem::get_comboBox_spotPrice_index() const {
    return ui->comboBox_spotPrice->currentIndex();
}

int PoolListWidgetItem::get_comboBox_secondToken_index() const {
    return ui->comboBox_secondToken->currentIndex();
}

void PoolListWidgetItem::set_comboBox_spotPrice_index(int index) {
    ui->comboBox_spotPrice->setCurrentIndex(index);
}

void PoolListWidgetItem::set_comboBox_secondToken_index(int index){
    ui->comboBox_secondToken->setCurrentIndex(index);
}

void PoolListWidgetItem::on_comboBox_spotPrice_currentIndexChanged(int index)
{
    if (index != -1) {
        ui->tableWidget_poolInformation->clearContents();
        ui->tableWidget_poolInformation->setRowCount(pool_->tokens().size() * 2);
        Token *input_token = qvariant_cast<Token *>(ui->comboBox_spotPrice->currentData());

        int curr_row = 0;
        for (auto token : pool_->tokens()) {
            ui->tableWidget_poolInformation->setVerticalHeaderItem(curr_row, new QTableWidgetItem(QString::fromStdString(token->name() + " volume")));

            ui->tableWidget_poolInformation->setItem(curr_row, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(pool_->GetQuantity(token)))));
            if (last_quantities_.size() > 0) {
                double delta_volume = pool_->GetQuantity(token) - last_quantities_[token];
                ui->tableWidget_poolInformation->setItem(curr_row, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(delta_volume))));
                if (delta_volume > 0) {
                    ui->tableWidget_poolInformation->item(curr_row, 1)->setForeground(QBrush(QColor(0, 150, 0)));
                } else if (delta_volume == 0) {
                    ui->tableWidget_poolInformation->item(curr_row, 1)->setForeground(QBrush(QColor(180, 90, 20)));
                } else {
                    ui->tableWidget_poolInformation->item(curr_row, 1)->setForeground(QBrush(QColor(150, 0, 0)));
                }
                ui->tableWidget_poolInformation->setItem(curr_row, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(last_quantities_[token]))));
            } else {
                ui->tableWidget_poolInformation->setItem(curr_row, 1, new QTableWidgetItem("-"));
                ui->tableWidget_poolInformation->setItem(curr_row, 2, new QTableWidgetItem("-"));
            }

            ++curr_row;

            ui->tableWidget_poolInformation->setVerticalHeaderItem(curr_row, new QTableWidgetItem(QString::fromStdString(token->name() + " price")));

            ui->tableWidget_poolInformation->setItem(curr_row, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(pool_->GetSpotPrice(input_token, token)))));
            if (last_quantities_.size() > 0) {
                double last_price = last_spot_prices_[input_token][token];
                double delta_price = pool_->GetSpotPrice(input_token, token) - last_price;
                ui->tableWidget_poolInformation->setItem(curr_row, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(delta_price))));
                if (delta_price > 0) {
                    ui->tableWidget_poolInformation->item(curr_row, 1)->setForeground(QBrush(QColor(0, 150, 0)));
                } else if (delta_price == 0) {
                    ui->tableWidget_poolInformation->item(curr_row, 1)->setForeground(QBrush(QColor(180, 90, 20)));
                } else {
                    ui->tableWidget_poolInformation->item(curr_row, 1)->setForeground(QBrush(QColor(150, 0, 0)));
                }
                ui->tableWidget_poolInformation->setItem(curr_row, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(last_price))));
            } else {
                ui->tableWidget_poolInformation->setItem(curr_row, 1, new QTableWidgetItem("-"));
                ui->tableWidget_poolInformation->setItem(curr_row, 2, new QTableWidgetItem("-"));
            }

            ++curr_row;
        }

        ui->comboBox_secondToken->clear();
        for (auto token : pool_->tokens()) {
            if (token != input_token) {
                ui->comboBox_secondToken->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
            }
        }
    }
}

void PoolListWidgetItem::Invariant_Curve(PROTOCOL curr_protocol, double input_token_quantity, double last_input_token_quantity, double output_token_quantity, double last_output_token_quantity) {
    QVector<double> curve_x(101), curve_y(101);
    QVector<double> curve_x_last(101), curve_y_last(101);
    if (curr_protocol == PROTOCOL::UNISWAP_V2) {
        double curr_invariant = input_token_quantity * output_token_quantity;
        for(int i = 0; i<101;i++) {

            curve_x[i] = 2*i*input_token_quantity/100;
            curve_y[i] = curr_invariant/curve_x[i];
        }
        ui->widgetGraph->addGraph();
        ui->widgetGraph->graph(0)->setLineStyle(QCPGraph::lsLine);
        ui->widgetGraph->graph(0)->setData(curve_x, curve_y);
        ui->widgetGraph->legend->removeItem(0);
        double last_invariant = last_input_token_quantity * last_output_token_quantity;
        if (last_invariant!=curr_invariant)
        {
            for(int i = 0; i<101;i++) {
                curve_x_last[i] = 2*i*last_input_token_quantity/100;
                curve_y_last[i] = last_invariant/curve_x_last[i];
            }
            ui->widgetGraph->addGraph();
            ui->widgetGraph->graph(1)->setLineStyle(QCPGraph::lsLine);
            ui->widgetGraph->graph(1)->setData(curve_x_last, curve_y_last);
            ui->widgetGraph->legend->removeItem(0);
        }

    }

}

void PoolListWidgetItem::on_comboBox_secondToken_currentIndexChanged(int index)
{
    if (index != -1) {
        Token *input_token = qvariant_cast<Token *>(ui->comboBox_spotPrice->currentData());
        Token *output_token = qvariant_cast<Token *>(ui->comboBox_secondToken->currentData());
        double input_token_quantity = pool_->GetQuantity(input_token);
        double output_token_quantity = pool_->GetQuantity(output_token);
        PROTOCOL curr_protocol = GetPoolType(pool_);

        QVector<double> input_quants(2), output_quants(2);

        input_quants[0] = input_token_quantity;
        output_quants[0] = output_token_quantity;
        ui->widgetGraph->clearGraphs();

        //ui->widgetGraph->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
        //ui->widgetGraph->graph(0)->setPen(QPen(Qt::blue,2));
        for(int i=0; i<ui->tableWidget_poolInformation->rowCount();i++){

            if(ui->tableWidget_poolInformation->verticalHeaderItem(i)->text() == QString::fromStdString(input_token->name()+" volume"))
            {
                input_quants[1] = ui->tableWidget_poolInformation->item(i,2)->text().toDouble();
            }

            if(ui->tableWidget_poolInformation->verticalHeaderItem(i)->text() == QString::fromStdString(output_token->name()+" volume"))
            {
                output_quants[1] = ui->tableWidget_poolInformation->item(i,2)->text().toDouble();
            }
        }
        Invariant_Curve(curr_protocol, input_quants[0], input_quants[1], output_quants[0], output_quants[1]);

        QCPGraph* curr_Point = new QCPGraph(ui->widgetGraph->xAxis, ui->widgetGraph->yAxis);
        curr_Point->setAdaptiveSampling(false);
        curr_Point->setLineStyle(QCPGraph::lsNone);
        curr_Point->setScatterStyle(QCPScatterStyle::ssCircle);
        curr_Point->setPen(QPen(QBrush(QColor(100,16,176)), 2));
        curr_Point->setName("current quantities");
        curr_Point->addData(input_quants[0], output_quants[0]);

        if (!last_quantities_.empty()) {
        QCPGraph* last_Point = new QCPGraph(ui->widgetGraph->xAxis, ui->widgetGraph->yAxis);
        last_Point->setAdaptiveSampling(false);
        last_Point->setLineStyle(QCPGraph::lsNone);
        last_Point->setScatterStyle(QCPScatterStyle::ssCircle);
        last_Point->setPen(QPen(QBrush(QColor(100,0,0)), 2));
        last_Point->setName("last quantities");
        last_Point->addData(input_quants[1], output_quants[1]);
        }

//        QCPLayoutGrid *subLayout = new QCPLayoutGrid;
//        ui->widgetGraph->plotLayout()->addElement(1, 0, subLayout);
//        subLayout->setMargins(QMargins(1, 0, 1, 1));
//        subLayout->addElement(0, 0, ui->widgetGraph->legend);
//        ui->widgetGraph->legend->setFillOrder(QCPLegend::foColumnsFirst);


        // give the axes some labels:
        ui->widgetGraph->xAxis->setLabel(QString::fromStdString(input_token->name()));
        ui->widgetGraph->yAxis->setLabel(QString::fromStdString(output_token->name()));
        // set axes ranges, so we see all data:
        ui->widgetGraph->xAxis->setRange(0, 2 * input_token_quantity);
        ui->widgetGraph->yAxis->setRange(0, 2 * output_token_quantity);

        ui->widgetGraph->legend->setVisible(true);

        ui->widgetGraph->replot();
        ui->widgetGraph->setFixedHeight(250);
    }
}


