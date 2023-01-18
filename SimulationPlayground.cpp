#include "SimulationPlayground.h"
#include "ui_SimulationPlayground.h"
#include "PoolGraphItem.h"
#include <QVector>
#include <random>

enum VIEW_METHOD {
    VIEW_QUANTITY,
    VIEW_PRICE
};
std::string getPoolName(PoolInterface *pool) {
    std::string name = "";

    for (Token *token : pool->tokens()) {
        name += token->name();
        name += " & ";
    }
    return std::string(name.begin(), name.end() - 3);
}

Q_DECLARE_METATYPE(VIEW_METHOD);

SimulationPlayground::SimulationPlayground(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationPlayground)
{
    ui->setupUi(this);
    market_ = new Market;
    market_->loadInitialScenario({{"ETH", 1012}, {"DAI", 10}, {"BTC", 5}}, PROTOCOL::UNISWAP_V2);
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    ui->listWidget->addItem(item);

    for (PoolInterface *pool : market_->GetMarketPools()) {
        ui->pool_comboBox->addItem(QString::fromStdString(getPoolName(pool)),
                                   QVariant::fromValue(pool));
    }
    ui->View_Options->addItem("View Quantity", QVariant::fromValue(VIEW_METHOD::VIEW_QUANTITY));
    ui->View_Options->addItem("View Spot Price", QVariant::fromValue(VIEW_METHOD::VIEW_PRICE));
    ui->View_Options->setCurrentIndex(0);

    test_token = market_->getToken("DAI");
}

SimulationPlayground::~SimulationPlayground() {
    delete ui;
}

void SimulationPlayground::on_runButton_clicked() {
    market_->runEpoch();

    if (ui->pool_comboBox->currentIndex() != -1) {
        QListWidgetItem *item = ui->listWidget->item(0);
        QWidget *item_widget = ui->listWidget->itemWidget(item);

        PoolGraphItem *pool_graph = qobject_cast<PoolGraphItem *>(item_widget);

        pool_graph->setViewMethod(qvariant_cast<VIEW_METHOD>(ui->View_Options->currentData()) == VIEW_METHOD::VIEW_QUANTITY);
        pool_graph->UpdateGraph();
    }
}

void SimulationPlayground::on_pool_comboBox_currentIndexChanged(int index) {
    if(index == -1)
        return;

    PoolInterface *pool = qvariant_cast<PoolInterface *>(ui->pool_comboBox->itemData(index));
    PoolGraphItem *pool_graph = new PoolGraphItem(this, pool);

    pool_graph->setViewMethod(qvariant_cast<VIEW_METHOD>(ui->View_Options->currentData()) == VIEW_METHOD::VIEW_QUANTITY);
    pool_graph->UpdateGraph();

    QListWidgetItem *item = ui->listWidget->item(0);
    item->setSizeHint(pool_graph->sizeHint());
    ui->listWidget->setItemWidget(item, pool_graph);
}

void SimulationPlayground::on_pushButton_customEpoch_clicked() {
    if(ui->lineEdit->text() == ""){
        QMessageBox::about(this, "Invalid Epoch Number", "Enter epoch number");
    }
    for(int i = 0; i < ui->lineEdit->text().toInt(); i++){
        on_runButton_clicked();
    }
}


void SimulationPlayground::on_pushButton_2_clicked() {
    delete market_;
    market_ = new Market();
    market_->loadInitialScenario({{"ETH", 1012}, {"DAI", 10}, {"BTC", 5}}, PROTOCOL::UNISWAP_V2);

    ui->pool_comboBox->clear();

    for (PoolInterface *pool : market_->GetMarketPools()) {
        ui->pool_comboBox->addItem(QString::fromStdString(getPoolName(pool)),
                                   QVariant::fromValue(pool));
    }
    ui->pool_comboBox->setCurrentIndex(0);
}


void SimulationPlayground::on_View_Options_currentIndexChanged(int index) {
    if (ui->pool_comboBox->currentIndex() == -1)
        return;

    PoolInterface *pool = qvariant_cast<PoolInterface *>(ui->pool_comboBox->currentData());
    PoolGraphItem *pool_graph = new PoolGraphItem(this, pool);

    pool_graph->setViewMethod(qvariant_cast<VIEW_METHOD>(ui->View_Options->itemData(index)) == VIEW_METHOD::VIEW_QUANTITY);
    pool_graph->UpdateGraph();

    QListWidgetItem *item = ui->listWidget->item(0);
    item->setSizeHint(pool_graph->sizeHint());
    ui->listWidget->setItemWidget(item, pool_graph);
}


