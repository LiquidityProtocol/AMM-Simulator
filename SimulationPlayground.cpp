#include "SimulationPlayground.h"
#include "ui_SimulationPlayground.h"
#include "PoolListWidgetItem.h"

SimulationPlayground::SimulationPlayground(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationPlayground)
{
    ui->setupUi(this);
    market_ = new Market;
    for(auto pool: market_->GetMarketPools()){
        VerifyUpdatePoolDisplayRequest(pool);
    }
}

SimulationPlayground::~SimulationPlayground()
{
    delete ui;
}

void SimulationPlayground::VerifyUpdatePoolDisplayRequest(PoolInterface *pool) {
    for (int i = 0; i < ui->listWidget_pool->count(); ++i) {
        QListWidgetItem *item = ui->listWidget_pool->item(i);
        QWidget *item_widget = ui->listWidget_pool->itemWidget(item);
        PoolListWidgetItem *old_pool_item = qobject_cast<PoolListWidgetItem *>(item_widget);
        if (old_pool_item->pool() == pool) {
            int input_token_idx = old_pool_item->get_comboBox_spotPrice_index();
            int second_token_idx = old_pool_item->get_comboBox_secondToken_index();
            PoolListWidgetItem *pool_item = new PoolListWidgetItem(this, pool, old_pool_item->curr_quantities(), old_pool_item->curr_spot_prices());
            pool_item->set_comboBox_spotPrice_index(input_token_idx);
            pool_item->set_comboBox_secondToken_index(second_token_idx);
            pool_item->on_comboBox_spotPrice_activated(input_token_idx);
            pool_item->on_comboBox_secondToken_activated(second_token_idx);
            item->setSizeHint(pool_item->sizeHint());
            ui->listWidget_pool->setItemWidget(item, pool_item);
            return;
        }
    }
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget_pool);
    ui->listWidget_pool->addItem(item);
    PoolListWidgetItem *pool_item = new PoolListWidgetItem(this, pool);
    item->setSizeHint(pool_item->sizeHint());
    ui->listWidget_pool->setItemWidget(item, pool_item);
}

void SimulationPlayground::on_pushButton_clicked()
{
    market_->runEpoch();
    for(auto pool: market_->GetMarketPools()){
        VerifyUpdatePoolDisplayRequest(pool);
    }
}

