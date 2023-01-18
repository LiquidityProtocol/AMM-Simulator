#ifndef LPGRAPHITEM_H
#define LPGRAPHITEM_H

#include "qcustomplot.h"
#include "src/Utilities/Utilities.hpp"
#include <QWidget>

namespace Ui {
class LPGraphItem;
}

class LPGraphItem : public QWidget
{
    Q_OBJECT

public:
    explicit LPGraphItem(QWidget *parent = nullptr, PoolInterface *pool = nullptr);
    ~LPGraphItem();

    void clearData();
    void UpdateGraph();
    void initLineChart();
    void set_LP_Profits(QVector<double> LP);

private:
    Ui::LPGraphItem *ui;

    PoolInterface *pool_;
    QVector<double> LP_Profits;

    int plotted_Epochs = 20;

};

#endif // LPGRAPHITEM_H
