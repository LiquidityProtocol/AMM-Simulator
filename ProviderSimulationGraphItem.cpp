#include "ProviderSimulationGraphItem.h"
#include "ui_ProviderSimulationGraphItem.h"

std::random_device rd_provider;
std::mt19937 gen1(rd_provider());
std::uniform_int_distribution<> distrib_provider(0, 255);


QColor random_color_provider() {
    int R = distrib_provider(gen1);
    int G = distrib_provider(gen1);
    int B = distrib_provider(gen1);

    QColor color(R, G, B);

    return color;
}

ProviderSimulationGraphItem::ProviderSimulationGraphItem(QWidget *parent, PoolInterface *pool, Provider* provider) :
    QWidget(parent),
    ui(new Ui::ProviderSimulationGraphItem),
    pool_(pool),
    provider_(provider)
{
    ui->setupUi(this);
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void ProviderSimulationGraphItem::UpdateGraph() {
    ui->widget->clearGraphs();
    QVector<double> hold_vals = provider_->calcHoldValue(pool_);
    QVector<double> share_vals = {};
    share_vals.fill(provider_->calcShareValue(pool_), hold_vals.size());
    QVector<double> epochs;
    for(int i = 0; i < hold_vals.size(); i++){
        epochs.push_back(i);
    }
    QCPGraph* line1 = ui->widget->addGraph();
    line1->setData(epochs, share_vals);
    line1->setName("Current Withdraw Value");
    line1->rescaleAxes(true);
    line1->setPen(QPen(QBrush(QColor(255,0,0)), 2));

    QCPGraph* line2 = ui->widget->addGraph();
    line2->setData(epochs, hold_vals);
    line2->setName("Hold Value");
    line2->rescaleAxes(true);
    line2->setPen(QPen(QBrush(QColor(0,255,0)), 2));


//    double xmin = epochs[0], xmax = epochs.back();
//    double ymin = 1e18, ymax = -1;


//    QCPGraph lines[2] = {line1, line2};

//    for (auto line : lines) {
//        ymin = std::min(ymin, *std::min_element(value[line].begin(), value[line].end()));
//        ymax = std::max(ymax, *std::max_element(value[line].begin(), value[line].end()));

//        line->(epochs, value[line]);
//        line->addToLegend();
//        line->rescaleAxes(true);


//    double xrange = xmax - xmin;
//    double yrange = ymax - ymin;

//    ui->widget->xAxis->setRange(std::max(0.0, xmin - xrange * 0.1), xmax + xrange * 0.1);
//    ui->widget->yAxis->setRange(std::max(0.0, ymin - yrange * 0.1), ymax + yrange * 0.1);

    ui->widget->xAxis->setLabel("Epochs");
    ui->widget->yAxis->setLabel("Value");
    ui->widget->legend->setVisible(true);
    ui->widget->replot();
}

void ProviderSimulationGraphItem::clearData() {

//    line1->data()->clear();
//    line1->removeFromLegend();

//    line2->data()->clear();
//    line2->removeFromLegend();
}




ProviderSimulationGraphItem::~ProviderSimulationGraphItem()
{
    delete ui;
}
