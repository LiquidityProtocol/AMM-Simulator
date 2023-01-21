#ifndef ARBITRAGEURSIMULATIONGRAPHITEM_H
#define ARBITRAGEURSIMULATIONGRAPHITEM_H
#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class ArbitrageurSimulationGraphItem;
}

class ArbitrageurSimulationGraphItem : public QWidget
{
    Q_OBJECT

public:
    explicit ArbitrageurSimulationGraphItem(QWidget *parent = nullptr, QVector<double> epochs={}, QVector<double> wallet_values={});
    ~ArbitrageurSimulationGraphItem();

    void clearData();
    void UpdateGraph(QVector<double> epochs_2, QVector<double> wallet_values_2);

private:
    Ui::ArbitrageurSimulationGraphItem *ui;
    QVector<double> epochs;
    QVector<double> wallet_values_;
    QCPGraph* arbitrager_to_graph;
};

#endif // ARBITRAGEURSIMULATIONGRAPHITEM_H

