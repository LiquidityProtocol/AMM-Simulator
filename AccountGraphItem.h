#ifndef ACCOUNTGRAPHITEM_H
#define ACCOUNTGRAPHITEM_H

#include "qcustomplot.h"
#include "src/Utilities/Utilities.hpp"
#include "src/Market/Agents/Arbitrager.hpp"
#include <QWidget>

namespace Ui {
class AccountGraphItem;
}

class AccountGraphItem : public QWidget
{
    Q_OBJECT

public:
    explicit AccountGraphItem(QWidget *parent = nullptr, Arbitrager *arbitrager=nullptr);
    ~AccountGraphItem();

    void UpdateGraph();

private:
    Ui::AccountGraphItem *ui;
    QCPGraph* arbitrager_to_graph;

    Arbitrager *arbitrager;
    QVector<double> *epochs;
    QVector<double> *wallet_values;

};

#endif // ACCOUNTGRAPHITEM_H
