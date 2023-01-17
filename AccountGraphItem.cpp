#include "AccountGraphItem.h"
#include "ui_AccountGraphItem.h"

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

AccountGraphItem::AccountGraphItem(QWidget *parent, Account *account) :
    QWidget(parent),
    ui(new Ui::AccountGraphItem)
{
    *wallet_values = {account->total_value()};
    ui->setupUi(this);
    account_to_graph[account_] = ui->widget->addGraph();
    account_to_graph[account_]->setName(QString::fromStdString(account->name()));
    account_to_graph[account_]->setPen(QPen(QBrush(QColor(random_color())), 2));
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void AccountGraphItem::UpdateGraph()
{
    // clear the data of previous graph
    account_to_graph[account_]->data()->clear();
    account_to_graph[account_]->removeFromLegend();

    // plot the data from the ledger
    QVector<double> new_epochs;

    for (unsigned int i = 0 ; i < (*epochs).size() + 1 ; ++i)
        new_epochs.append(i);

    *epochs = new_epochs;

    (*wallet_values).append(account_->total_value());

    account_to_graph[account_]->setData(*epochs, *wallet_values);
    account_to_graph[account_]->addToLegend();
    account_to_graph[account_]->rescaleAxes(true);

    ui->widget->xAxis->setLabel("Epochs");
    ui->widget->yAxis->setLabel("Value of the wallet");
    ui->widget->legend->setVisible(true);
    ui->widget->replot();
}

AccountGraphItem::~AccountGraphItem()
{
    delete ui;
}
