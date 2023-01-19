#include "ProviderSimulationGraphItem.h"
#include "ui_ProviderSimulationGraphItem.h"

std::random_device rd_provider;
std::mt19937 gen(rd_provider());
std::uniform_int_distribution<> distrib_provider(0, 255);


QColor random_color_provider() {
    int R = distrib_provider(gen);
    int G = distrib_provider(gen);
    int B = distrib_provider(gen);

    QColor color(R, G, B);

    return color;
}

ProviderSimulationGraphItem::ProviderSimulationGraphItem(QWidget *parent, PoolInterface *pool) :
    QWidget(parent),
    ui(new Ui::ProviderSimulationGraphItem),
    pool_(pool),
    provider_(provider)
{
    ui->setupUi(this);
    line1 = ui->widget->addGraph();
    line1->setName(QString::fromStdString('Current Withdraw Value'));
    line1->setPen(QPen(QBrush(QColor(random_color())), 2));

    line2 = ui->widget->addGraph();
    line2->setName(QString::fromStdString('Hold Value'));
    line2->setPen(QPen(QBrush(QColor(random_color())), 2));

    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void PoolGraphItem::UpdateGraph() {
    clearData();

    std::vector<Operation *> opsList = pool_->GetLatestEpochs(plotted_Epochs);
    QVector<double> epochs;


    std::vector<double> hold_vals;
    std::vector<double> share_vals;
    provider.calcHoldValue(pool, hold_vals);
    provider.calcShareValue(pool, share_vals);

    if (opsList.empty())
        return;

    for (auto ops : opsList) {
        assert(ops->endEpoch());
        epochs.append(ops->epochIndex());
    }

    double xmin = epochs[0], xmax = epochs.back();
    double ymin = 1e18, ymax = -1;

    std::unordered_map<QCPGraph*, QVector<double> > value;
    value[line1] = hold_vals;
    value[line2] = share_vals;

    QCPGraph lines[2] = {line1, line2};


    for (auto line : lines) {
        ymin = std::min(ymin, *std::min_element(value[line].begin(), value[line].end()));
        ymax = std::max(ymax, *std::max_element(value[line].begin(), value[line].end()));

        line->setData(epochs, value[line]);
        line->addToLegend();
        line->rescaleAxes(true);


    double xrange = xmax - xmin;
    double yrange = ymax - ymin;

    ui->widget->xAxis->setRange(std::max(0.0, xmin - xrange * 0.1), xmax + xrange * 0.1);
    ui->widget->yAxis->setRange(std::max(0.0, ymin - yrange * 0.1), ymax + yrange * 0.1);

    ui->widget->xAxis->setLabel("Epochs");
    ui->widget->yAxis->setLabel("Value");
    ui->widget->legend->setVisible(true);
    ui->widget->replot();
}

void PoolGraphItem::clearData() {

    line1->data()->clear();
    line1->removeFromLegend();

    line2->data()->clear();
    line2->removeFromLegend();

}




ProviderSimulationGraphItem::~ProviderSimulationGraphItem()
{
    delete ui;
}
