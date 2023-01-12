#include "SimulationPlayground.h"
#include "ui_SimulationPlayground.h"
#include "PoolGraphItem.h"
#include <QVector>
#include <random>
#include <stdlib.h>
#include <unistd.h>

SimulationPlayground::SimulationPlayground(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationPlayground)
{
    ui->setupUi(this);
    market_ = new Market;
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    ui->listWidget->addItem(item);
    for (auto pool: market_->GetMarketPools()){
        std::string name;
        for (auto token: pool->tokens()){
            name += token->name() + " & ";
        }
        QString pool_name = QString::fromStdString(std::string(name.begin(), name.end() - 3));
        ui->pool_comboBox->addItem(pool_name, QVariant::fromValue(pool));
    }
    test_token = market_->getToken("UNI");

}

SimulationPlayground::~SimulationPlayground()
{
    delete ui;
}


void SimulationPlayground::on_pushButton_clicked()
{
    market_->runEpoch();
    QListWidgetItem *item = ui->listWidget->item(0);
    QWidget *item_widget = ui->listWidget->itemWidget(item);
    PoolGraphItem *pool_graph = qobject_cast<PoolGraphItem *>(item_widget);
    pool_graph->UpdateGraph();
}


void SimulationPlayground::on_pool_comboBox_currentIndexChanged(int index)
{
    PoolInterface *pool = qvariant_cast<PoolInterface *>(ui->pool_comboBox->itemData(index));
    PoolGraphItem *pool_graph = new PoolGraphItem(this, pool);
    pool_graph->UpdateGraph();
    QListWidgetItem *item = ui->listWidget->item(0);
    item->setSizeHint(pool_graph->sizeHint());
    ui->listWidget->setItemWidget(item, pool_graph);
}


void SimulationPlayground::on_pushButton_customEpoch_clicked()
{
    if(ui->lineEdit->text() == ""){
        QMessageBox::about(this, "Invalid Epoch Number", "Enter epoch number");
    }
    for(int i = 0; i < ui->lineEdit->text().toInt(); i++){
//        unistd::sleep(1000);
        on_pushButton_clicked();
    }
}


void SimulationPlayground::on_pushButton_2_clicked()
{
//    delete market_;
//    market_ = new Market();
//    ui->pool_comboBox->setCurrentIndex(-1);
}

