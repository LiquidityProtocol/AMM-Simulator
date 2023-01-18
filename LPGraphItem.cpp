#include "LPGraphItem.h"
#include "ui_LPGraphItem.h"

LPGraphItem::LPGraphItem(QWidget *parent, PoolInterface *pool) :
    QWidget(parent),
    ui(new Ui::LPGraphItem),
    pool_(pool)
{
    ui->setupUi(this);

    ui->LPGraphwidget->xAxis->setLabel("Epochs");
    ui->LPGraphwidget->yAxis->setLabel("LP Returns");
    ui->LPGraphwidget->legend->setVisible(true);
    ui->LPGraphwidget->replot();
//    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}


LPGraphItem::~LPGraphItem()
{
    delete ui;
}

void LPGraphItem::set_LP_Profits(QVector<double> LP) {
    LP_Profits = LP;
}

void LPGraphItem::UpdateGraph() {

    if (LP_Profits.size()>=20) {
    ui->LPGraphwidget->clearGraphs();

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

    ymin = std::min(ymin, *std::min_element(LP_Profits.begin(), LP_Profits.end()));
    ymax = std::max(ymax, *std::max_element(LP_Profits.begin(), LP_Profits.end()));

    double xrange = xmax - xmin;
    double yrange = ymax - ymin;

    ui->LPGraphwidget->xAxis->setRange(std::max(0.0, xmin - xrange * 0.1), xmax + xrange * 0.1);
    ui->LPGraphwidget->yAxis->setRange(std::max(0.0, ymin - yrange * 0.1), ymax + yrange * 0.1);

    QVector<double> LP_last(LP_Profits.end() - 20, LP_Profits.end());

    QCPGraph *lineChart = new QCPGraph(ui->LPGraphwidget->xAxis, ui->LPGraphwidget->yAxis);
    lineChart->setLineStyle(QCPGraph::lsLine);
    lineChart->setData(epochs, LP_last);
    ui->LPGraphwidget->replot();
    }
}



