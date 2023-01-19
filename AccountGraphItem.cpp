#include "AccountGraphItem.h"
#include "ui_AccountGraphItem.h"

std::random_device rd2;
std::mt19937 gen2(rd2());
std::uniform_int_distribution<> distrib2(0, 255);

QColor random_color2() {
    int R = distrib2(gen2);
    int G = distrib2(gen2);
    int B = distrib2(gen2);

    QColor color(R, G, B);

    return color;
}

AccountGraphItem::AccountGraphItem(QWidget *parent, Arbitrager *arbitrager) :
    QWidget(parent),
    ui(new Ui::AccountGraphItem)
{
    /**wallet_values = {arbitrager->total_value()};
    ui->setupUi(this);
    arbitrager_to_graph = ui->widget->addGraph();
    arbitrager_to_graph->setName(QString::fromStdString(arbitrager->name()));
    arbitrager_to_graph->setPen(QPen(QBrush(QColor(random_color2())), 2));
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);*/
}

void AccountGraphItem::UpdateGraph()
{
    /* // clear the data of previous graph
    arbitrager_to_graph->data()->clear();
    arbitrager_to_graph->removeFromLegend();

    // plot the data
    QVector<double> new_epochs;

    for (unsigned int i = 0 ; i < (*epochs).size() + 1 ; ++i)
        new_epochs.append(i);

    *epochs = new_epochs;

    (*wallet_values).append((*arbitrager).total_value());

    arbitrager_to_graph->setData(*epochs, *wallet_values);
    arbitrager_to_graph->addToLegend();
    arbitrager_to_graph->rescaleAxes(true);

    ui->widget->xAxis->setLabel("Epochs");
    ui->widget->yAxis->setLabel("Value of the wallet");
    ui->widget->legend->setVisible(true);
    ui->widget->replot(); */
}

AccountGraphItem::~AccountGraphItem()
{
    delete ui;
}
