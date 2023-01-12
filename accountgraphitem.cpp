#include <cmath>
#include "accountgraphitem.h"
#include "ui_accountgraphitem.h"

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

accountgraphitem::accountgraphitem(QWidget *parent, Account *account) :
    QWidget(parent),
    ui(new Ui::accountgraphitem),
    account_(account)
{
    ui->setupUi(this);
    token_to_graph = std::unordered_map< Token*, QCPGraph* > ();
    for (auto token: account_->tokens()){
        token_to_graph[token] = ui->widget->addGraph();
        token_to_graph[token]->setName(QString::fromStdString(token->name()));
        token_to_graph[token]->setPen(QPen(QBrush(QColor(random_color())), 2));

        for (auto token2 : account_->tokens()) if (token->name() != token2->name()) {
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

void accountgraphitem::UpdateGraph() {
    // clear the data of previous graph
    for (auto token1 : account_->tokens())
    for (auto token2 : account_->tokens()) if (token1->name() != token2->name()) {
        pToken_to_graph[token1][token2]->data()->clear();
        pToken_to_graph[token1][token2]->removeFromLegend();
    }
    for (auto token : account_->tokens()) {
        token_to_graph[token]->data()->clear();
        token_to_graph[token]->removeFromLegend();
    }

    // plot the data from the ledger
    std::vector<Operation *> accountLedger = account_->ledger();
    QVector<double> epochs;

    for (size_t i = 0 ; i < accountLedger.size() ; ++i)
        epochs.append(i);

    if (plotting_inventory) {
        std::unordered_map<Token*, QVector<double> > inventory_quantities;

        for (auto ops : accountLedger)
        for (auto token : account_->tokens())
            inventory_quantities[token].append(ops->GetQuanitty(token));

        for (auto token : account_->tokens()) {
            token_to_graph[token]->setData(epochs, inventory_quantities[token]);
            token_to_graph[token]->addToLegend();
            token_to_graph[token]->rescaleAxes(true);
        }
    } else {
        QVector<double> spotPriceHistory;

        for (auto ops : accountLedger)
            spotPriceHistory.append(ops->GetSpotPrice(plottedToken1, plottedToken2));

        pToken_to_graph[plottedToken1][plottedToken2]->setData(epochs, spotPriceHistory);
        pToken_to_graph[plottedToken1][plottedToken2]->addToLegend();
        pToken_to_graph[plottedToken1][plottedToken2]->rescaleAxes(true);
    }
    ui->widget->xAxis->setLabel("Epochs");
    ui->widget->yAxis->setLabel(plotting_inventory ? "Quantity" : "Spot Price");
    ui->widget->legend->setVisible(true);
    ui->widget->replot();
}
accountGraphItem::~accountGraphItem()
{
    delete ui;
}
