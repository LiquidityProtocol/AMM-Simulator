#include "SimulationPlayground.h"
#include "ui_SimulationPlayground.h"
#include "PoolGraphItem.h"
#include "AccountGraphItem.h"
#include <QVector>
#include <random>
#include<unistd.h>               // for linux

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
    for (auto account: market_->GetMarketAccounts()){
        QString account_name = QString::fromStdString(account->name());
        ui->comboBox->addItem(account_name);
        ui->comboBox_2->addItem(account_name);
    }
    test_token = market_->getToken("UNI");
    QListWidgetItem *arbitrager = new QListWidgetItem(ui->listWidget2);
    ui->listWidget2->addItem(arbitrager);
    QListWidgetItem *provider = new QListWidgetItem(ui->listWidget3);
    ui->listWidget3->addItem(provider);
}


SimulationPlayground::~SimulationPlayground()
{
    delete ui;
}


void SimulationPlayground::on_pushButton_clicked()
{
    market_->runEpoch();
    if(ui->pool_comboBox->currentIndex() != -1){
        QListWidgetItem *item = ui->listWidget->item(0);
        QWidget *item_widget = ui->listWidget->itemWidget(item);
        PoolGraphItem *pool_graph = qobject_cast<PoolGraphItem *>(item_widget);
        pool_graph->UpdateGraph();
    }
    if(ui->comboBox->currentIndex() != -1){
        QListWidgetItem *arbitrager = ui->listWidget2->item(0);
        QWidget *arbitrager_widget = ui->listWidget2->itemWidget(arbitrager);
        AccountGraphItem *arbitrager_graph = qobject_cast<AccountGraphItem *>(arbitrager_widget);
        arbitrager_graph->UpdateGraph();
    }
    if(ui->comboBox_2->currentIndex() != -1){
        QListWidgetItem *provider = ui->listWidget3->item(0);
        QWidget *provider_widget = ui->listWidget3->itemWidget(provider);
        AccountGraphItem *provider_graph = qobject_cast<AccountGraphItem *>(provider_widget);
        provider_graph->UpdateGraph();
    }
}


void SimulationPlayground::on_pool_comboBox_currentIndexChanged(int index)
{
    if(index == -1){
        return;
    }
    PoolInterface *pool = qvariant_cast<PoolInterface *>(ui->pool_comboBox->itemData(index));
    PoolGraphItem *pool_graph = new PoolGraphItem(this, pool);
    pool_graph->UpdateGraph();
    QListWidgetItem *item = ui->listWidget->item(0);
    item->setSizeHint(pool_graph->sizeHint());
    ui->listWidget->setItemWidget(item, pool_graph);
}

void SimulationPlayground::on_comboBox_currentIndexChanged(int index2)
{
    if(index2 == -1){
        return;
    }
    Account *arbitrager = qvariant_cast<Account *>(ui->comboBox->itemData(index2));
    AccountGraphItem *arbitrager_graph = new AccountGraphItem(this, arbitrager);
    arbitrager_graph->UpdateGraph();
    QListWidgetItem *item2 = ui->listWidget2->item(0);
    item2->setSizeHint(arbitrager_graph->sizeHint());
    ui->listWidget2->setItemWidget(item2, arbitrager_graph);
}

void SimulationPlayground::on_comboBox_2_currentIndexChanged(int index3)
{
    if(index3 == -1){
        return;
    }
    Account *provider = qvariant_cast<Account *>(ui->comboBox_2->itemData(index3));
    AccountGraphItem *provider_graph = new AccountGraphItem(this, provider);
    provider_graph->UpdateGraph();
    QListWidgetItem *item3 = ui->listWidget3->item(0);
    item3->setSizeHint(provider_graph->sizeHint());
    ui->listWidget3->setItemWidget(item3, provider_graph);
}


void SimulationPlayground::on_pushButton_customEpoch_clicked()
{
    if(ui->lineEdit->text() == ""){
        QMessageBox::about(this, "Invalid Epoch Number", "Enter epoch number");
    }
    for(int i = 0; i < ui->lineEdit->text().toInt(); i++){
        on_pushButton_clicked();
//        sleep(1);
    }
}


void SimulationPlayground::on_pushButton_2_clicked()
{
    delete market_;
    market_ = new Market();
    ui->pool_comboBox->clear();
    for (auto pool: market_->GetMarketPools()){
        std::string name;
        for (auto token: pool->tokens()){
            name += token->name() + " & ";
        }
        QString pool_name = QString::fromStdString(std::string(name.begin(), name.end() - 3));
        ui->pool_comboBox->addItem(pool_name, QVariant::fromValue(pool));
    }
    ui->pool_comboBox->setCurrentIndex(0);
    for (auto account: market_->GetMarketAccounts()){
        QString account_name = QString::fromStdString(account->name());
        ui->comboBox->addItem(account_name);
        ui->comboBox_2->addItem(account_name);
    }
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
}

