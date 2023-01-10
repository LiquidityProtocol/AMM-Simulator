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
    explicit PoolGraphItem(QWidget *parent = nullptr, PoolInterface *pool=nullptr);
    ~PoolGraphItem();
    void UpdateGraph();

private:
    Ui::PoolGraphItem *ui;
    std::unordered_map<Token*, QVector<double> > inventory_quantities;
    std::unordered_map< Token*, QCPGraph* > token_to_graph;
    PoolInterface *pool_;
    QVector<double> epochs;
};

#endif // POOLGRAPHITEM_H
