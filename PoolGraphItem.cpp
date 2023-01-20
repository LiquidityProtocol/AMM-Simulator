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
    connect(ui->widget, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseHover(QMouseEvent*)));

    mouseHorizontal = new QCPItemStraightLine(ui->widget);
    mouseVertical = new QCPItemStraightLine(ui->widget);

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
    initEpochContent();

    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void PoolGraphItem::mouseHover(QMouseEvent *event) {
    double x = ui->widget->xAxis->pixelToCoord(event->pos().x()) + 0.5;
    double y = ui->widget->yAxis->pixelToCoord(event->pos().y());

    mouseHorizontal->point1->setCoords((int)x, 0);
    mouseHorizontal->point2->setCoords((int)x, 1);

    mouseVertical->point1->setCoords(0, y);
    mouseVertical->point2->setCoords(1, y);

    ui->widget->replot();
    ui->widget->yAxis->setTickLabels(plotting_volume);

    epochContent->setText("");

    PoolEpochData *dt = pool_->kthFirstEpoch((int)x);
    std::string content = "";

    if (dt == nullptr)
        return;

    if (plotting_volume) {
        for (auto token : pool_->tokens()) {
            std::string TokenContent = token->name();

            TokenContent += std::string(7 - TokenContent.size(), ' ');
            TokenContent += std::to_string(dt->GetVolume(token));

            content += TokenContent;
            content += "\n";
        }
        content.pop_back();
    } else {
        double open = dt->GetOpenPrice(plottedToken1, plottedToken2);
        double high = dt->GetHighPrice(plottedToken1, plottedToken2);
        double low = dt->GetLowPrice(plottedToken1, plottedToken2);
        double close = dt->GetClosePrice(plottedToken1, plottedToken2);

        if (open > close) {
            epochContent->setColor(QColor(Qt::red));
        } else {
            epochContent->setColor(QColor(Qt::green));
        }
        content += "O: " + std::to_string(open) + "\n";
        content += "H: " + std::to_string(high) + "\n";
        content += "L: " + std::to_string(low) + "\n";
        content += "C: " + std::to_string(close);
    }
    epochContent->setText(QString::fromStdString(content));
}

void PoolGraphItem::UpdateGraph() {
    clearData();

    std::vector<PoolEpochData *> history = pool_->GetEpochHistory();
    QVector<double> epochs;

    if (history.empty())
        return;

    for (auto epochData : history)
        epochs.append(epochData->epochIndex());

    double xmin = std::max(0.0, epochs.back() - plotted_Epochs), xmax = xmin + plotted_Epochs;
    double ymin = 1e18, ymax = -1;

    if (plotting_volume) {
        for (auto token : pool_->tokens()) {
            QVector<double> volume;

            for (auto epochData : history)
                volume.append(log(epochData->GetVolume(token)));

            ymin = std::min(ymin, *std::min_element(volume.begin(), volume.end()));
            ymax = std::max(ymax, *std::max_element(volume.begin(), volume.end()));

            token_to_graph[token]->setData(epochs, volume);
            token_to_graph[token]->addToLegend();
            token_to_graph[token]->rescaleAxes(true);
        }
    } else {
        QVector<double> open, high, low, close;

        for (auto ops : history) {
            open.append(ops->GetOpenPrice(plottedToken1, plottedToken2));
            high.append(ops->GetHighPrice(plottedToken1, plottedToken2));
            low.append(ops->GetLowPrice(plottedToken1, plottedToken2));
            close.append(ops->GetClosePrice(plottedToken1, plottedToken2));
        }
        epochs.resize(open.size());

        ymin = *std::min_element(low.begin(), low.end());
        ymax = *std::max_element(high.begin(), high.end());

        lineChart->addToLegend();
        lineChart->setData(epochs, close);
        lineChart->setName(QString::fromStdString(plottedToken2->name() + "/" + plottedToken1->name()));
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
    lineChart->setName(QString::fromStdString(plottedToken2->name() + "/" + plottedToken1->name()));
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

void PoolGraphItem::initEpochContent() {
    epochContent = new QCPItemText(ui->widget);
    epochContent->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    epochContent->position->setType(QCPItemPosition::ptAxisRectRatio);
    epochContent->position->setCoords(0.5, 0); // place position at center/top of axis rect
}

void PoolGraphItem::setViewMethod(bool plotting_volume) {
    this->plotting_volume = plotting_volume;
}
PoolGraphItem::~PoolGraphItem() {
    delete ui;
}
