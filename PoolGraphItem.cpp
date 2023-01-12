#include <cmath>

#include "PoolGraphItem.h"
#include "ui_PoolGraphItem.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(0, 255);

QColor random_color() {
    int R = distrib(gen);
    int G = distrib(gen);
    int B = distrib(gen);

    QColor color(R, G, B);

    return color;
}


PoolGraphItem::PoolGraphItem(QWidget *parent, PoolInterface *pool) :
    QWidget(parent),
    ui(new Ui::PoolGraphItem),
    pool_(pool)
{
    ui->setupUi(this);
    epochs = QVector<double>(0);
    inventory_quantities = std::unordered_map<Token*, QVector<double> >();
    token_to_graph = std::unordered_map< Token*, QCPGraph* > ();
    for (auto token: pool_->tokens()){
        token_to_graph[token] = ui->widget->addGraph();
        token_to_graph[token]->setName(QString::fromStdString(token->name()));
        token_to_graph[token]->setPen(QPen(QBrush(QColor(random_color())), 2));

        for (auto token2 : pool_->tokens()) if (token->name() != token2->name()) {
            std::string NAME = token->name() + "/" + token2->name();

            pToken_to_graph[token][token2] = ui->widget->addGraph();
            pToken_to_graph[token][token2]->setName(QString::fromStdString(NAME));
            pToken_to_graph[token][token2]->setPen(QPen(QBrush(QColor(random_color())), 2));
        }
        plottedToken1 = (plottedToken1 == nullptr ? token : plottedToken1);
        plottedToken2 = token;
    }
    assert(plottedToken1);
    assert(plottedToken2);
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void PoolGraphItem::UpdateContent() {
    epochs.push_back(epochs.size());
    for(auto [token, quantity]: pool_->quantities()){
        inventory_quantities[token].push_back(quantity);
    }
    for (Token *a : pool_->tokens())
    for (Token *b : pool_->tokens())
        spotPrices[a][b].append(log(pool_->GetSpotPrice(a, b)));
}

void PoolGraphItem::UpdateGraph() {
    UpdateContent();
    if (plotting_inventory) {
        for (auto token1 : pool_->tokens())
        for (auto token2 : pool_->tokens()) if (token1->name() != token2->name()) {
            pToken_to_graph[token1][token2]->data()->clear();
            pToken_to_graph[token1][token2]->removeFromLegend();
        }

        for (auto token : pool_->tokens()) {
            token_to_graph[token]->setData(epochs, inventory_quantities[token]);
            token_to_graph[token]->addToLegend();
            token_to_graph[token]->rescaleAxes(true);
        }
    } else {
        for (auto token : pool_->tokens()) {
            token_to_graph[token]->data()->clear();
            token_to_graph[token]->removeFromLegend();
        }
        for (auto token1 : pool_->tokens())
        for (auto token2 : pool_->tokens()) if (token1->name() != token2->name()) {
            pToken_to_graph[token1][token2]->data()->clear();
            pToken_to_graph[token1][token2]->removeFromLegend();
        }

        pToken_to_graph[plottedToken1][plottedToken2]->setData(epochs, spotPrices[plottedToken1][plottedToken2]);
        pToken_to_graph[plottedToken1][plottedToken2]->addToLegend();
        pToken_to_graph[plottedToken1][plottedToken2]->rescaleAxes(true);
    }
    ui->widget->xAxis->setLabel("Epochs");
    ui->widget->yAxis->setLabel(plotting_inventory ? "Quantity" : "Spot Price");
    ui->widget->legend->setVisible(true);
    ui->widget->replot();
}
PoolGraphItem::~PoolGraphItem()
{
    delete ui;
}
