#include "ArbitrageurSimulationGraphItem.h"
#include "qcustomplot.h"
#include "ui_ArbitrageurSimulationGraphItem.h"

std::random_device rd10;
std::mt19937 gen10(rd10());
std::uniform_int_distribution<> distrib10(0, 255);

QColor random_color10() {
    int R = distrib10(gen10);
    int G = distrib10(gen10);
    int B = distrib10(gen10);

    QColor color(R, G, B);

    return color;
}

ArbitrageurSimulationGraphItem::ArbitrageurSimulationGraphItem(QWidget *parent, QVector<double> epochs, QVector<double> wallet_values) :
    QDialog(parent),
    ui(new Ui::ArbitrageurSimulationGraphItem),
    wallet_values_(wallet_values)
{
    ui->setupUi(this);
    QCPGraph *arbitrager_to_graph = ui->widget->addGraph();
    arbitrager_to_graph->setName(QString::fromStdString("Arbitrageur's wallet value"));
    arbitrager_to_graph->setPen(QPen(QBrush(QColor(random_color10())), 2));
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    arbitrager_to_graph->setData(epochs, wallet_values);
    arbitrager_to_graph->addToLegend();
    arbitrager_to_graph->rescaleAxes(true);

    ui->widget->xAxis->setLabel("Epochs");
    ui->widget->yAxis->setLabel("Value of the wallet");
    ui->widget->legend->setVisible(true);
    ui->widget->replot();
}


ArbitrageurSimulationGraphItem::~ArbitrageurSimulationGraphItem()
{
    delete ui;
}
