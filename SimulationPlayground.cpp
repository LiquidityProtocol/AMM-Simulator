#include "SimulationPlayground.h"
#include "ui_SimulationPlayground.h"
#include "PoolGraphItem.h"
#include <QVector>
#include <random>


SimulationPlayground::SimulationPlayground(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationPlayground)
{
    ui->setupUi(this);
    market_ = new Market;
    for (auto pool: market_->GetMarketPools()){
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        PoolGraphItem *pool_graph = new PoolGraphItem(this, pool);
        item->setSizeHint(pool_graph->sizeHint());
        ui->listWidget->setItemWidget(item, pool_graph);
    }

    test_token = market_->getToken("UNI");
//    token_to_graph[test_token] = ui->widget_pool_inventory->addGraph();

}

SimulationPlayground::~SimulationPlayground()
{
    delete ui;
}


void SimulationPlayground::on_pushButton_clicked()
{
    market_->runEpoch();
    for(int i = 0; i < ui->listWidget->count(); ++i){
        QListWidgetItem *item = ui->listWidget->item(i);
        QWidget *item_widget = ui->listWidget->itemWidget(item);
        PoolGraphItem *pool_graph = qobject_cast<PoolGraphItem *>(item_widget);
        pool_graph->UpdateGraph();
    }
}

