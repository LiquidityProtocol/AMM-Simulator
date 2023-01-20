#ifndef POOLGRAPHITEM_H
#define POOLGRAPHITEM_H

#include "qcustomplot.h"
#include "src/Utilities/Utilities.hpp"
#include <QWidget>

namespace Ui {
class PoolGraphItem;
}

class PoolGraphItem : public QWidget
{
    Q_OBJECT

public:
    explicit PoolGraphItem(QWidget *parent = nullptr, PoolInterface *pool = nullptr);

    ~PoolGraphItem();

    void clearData();
    void UpdateGraph();

    void initLineChart();
    void initCandleStick();
    void initEpochContent();
    void initHoverLines();

    void setViewMethod(bool plotting_volume);
private slots:
    void mouseHover(QMouseEvent *event);
private:
    Ui::PoolGraphItem *ui;

    std::unordered_map<Token*, QCPGraph*> token_to_graph;

    PoolInterface *pool_;

    QCPFinancial *candleStick;
    QCPGraph *lineChart;

    Token *plottedToken1 = nullptr;
    Token *plottedToken2 = nullptr;

    bool plotting_volume = true;
    int plotted_Epochs = 20;

    QCPItemStraightLine *mouseHorizontal;
    QCPItemStraightLine *mouseVertical;
    QCPItemText *epochContent;
};

#endif // POOLGRAPHITEM_H
