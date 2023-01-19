#include <cmath>
#include <iostream>

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
    token_to_graph = std::unordered_map< Token*, QCPGraph* > ();
    for (auto token: pool_->tokens()){
        token_to_graph[token] = ui->widget->addGraph();
        token_to_graph[token]->setName(QString::fromStdString(token->name()));
        token_to_graph[token]->setPen(QPen(QBrush(QColor(random_color())), 2));

        plottedToken1 = (plottedToken1 == nullptr ? token : plottedToken1);
        plottedToken2 = token;
    }
    initLineChart();
    initCandleStick();

    assert(plottedToken1);
    assert(plottedToken2);
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void PoolGraphItem::UpdateGraph() {
    clearData();

    std::vector<Operation *> opsList = pool_->GetLatestEpochs(plotted_Epochs);
    QVector<double> epochs;

    if (opsList.empty())
        return;

    for (auto ops : opsList) {
        assert(ops->endEpoch());
        epochs.append(ops->epochIndex());
    }

    double xmin = epochs[0], xmax = epochs.back();
    double ymin = 1e18, ymax = -1;

    if (plotting_volume) {
        std::unordered_map<Token*, QVector<double> > volume;

        for (auto ops : opsList)
        for (auto token : pool_->tokens())
            volume[token].append(ops->GetVolume(token));

        for (auto token : pool_->tokens()) {
            ymin = std::min(ymin, *std::min_element(volume[token].begin(), volume[token].end()));
            ymax = std::max(ymax, *std::max_element(volume[token].begin(), volume[token].end()));

            token_to_graph[token]->setData(epochs, volume[token]);
            token_to_graph[token]->addToLegend();
            token_to_graph[token]->rescaleAxes(true);
        }
    } else {
        QVector<double> open, high, low, close;

        for (auto ops : opsList) {
            open.append(ops->GetOpenPrice(plottedToken1, plottedToken2));
            high.append(ops->GetHighPrice(plottedToken1, plottedToken2));
            low.append(ops->GetLowPrice(plottedToken1, plottedToken2));
            close.append(ops->GetClosePrice(plottedToken1, plottedToken2));
        }
        epochs.resize(open.size());

        ymin = *std::min_element(low.begin(), low.end());
        ymax = *std::max_element(high.begin(), high.end());

        lineChart->setData(epochs, close);
        lineChart->setName(QString::fromStdString(plottedToken1->name() + "/" + plottedToken2->name()));
        candleStick->setData(epochs, open, high, low, close);
    }
    double xrange = xmax - xmin;
    double yrange = ymax - ymin;

    ui->widget->xAxis->setRange(std::max(0.0, xmin - xrange * 0.1), xmax + xrange * 0.1);
    ui->widget->yAxis->setRange(std::max(0.0, ymin - yrange * 0.1), ymax + yrange * 0.1);

    ui->widget->xAxis->setLabel("Epochs");
    ui->widget->yAxis->setLabel(plotting_volume ? "Volume" : "Price");
    ui->widget->legend->setVisible(true);
    ui->widget->replot();
}

void PoolGraphItem::clearData() {
    for (auto token : pool_->tokens()) {
        token_to_graph[token]->data()->clear();
        token_to_graph[token]->removeFromLegend();
    }
    lineChart->data()->clear();
    lineChart->removeFromLegend();

    candleStick->data()->clear();
    candleStick->removeFromLegend();
}

void PoolGraphItem::initLineChart() {
    lineChart = new QCPGraph(ui->widget->xAxis, ui->widget->yAxis);
    //  lineChart->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,
    //                             QPen(Qt::black, 1.5), QBrush(Qt::white), 3));
    lineChart->setLineStyle(QCPGraph::lsLine);
    lineChart->setPen(QPen(QColor(120, 120, 120), 3));
    lineChart->keyAxis()->setUpperEnding(QCPLineEnding::esSpikeArrow);
    lineChart->valueAxis()->setUpperEnding(QCPLineEnding::esSpikeArrow);

    QBrush shadowBrush(QColor(0, 0, 0), Qt::Dense7Pattern);
    lineChart->setBrush(shadowBrush);
    lineChart->setName("Line chart");
}

void PoolGraphItem::initCandleStick() {
    candleStick = new QCPFinancial(ui->widget->xAxis,
                                   ui->widget->yAxis);
    candleStick->setChartStyle(QCPFinancial::csCandlestick);
    candleStick->setTwoColored(true);
    candleStick->setName("Candlestick");
}

void PoolGraphItem::setViewMethod(bool plotting_volume) {
    this->plotting_volume = plotting_volume;
}
PoolGraphItem::~PoolGraphItem() {
    delete ui;
}
