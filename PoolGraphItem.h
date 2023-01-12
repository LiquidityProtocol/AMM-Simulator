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

    void UpdateContent();
    void UpdateGraph();

private:
    Ui::PoolGraphItem *ui;

    std::unordered_map<Token*, std::unordered_map<Token*, QVector<double> > > spotPrices;
    std::unordered_map<Token*, std::unordered_map<Token*, QCPGraph*> > pToken_to_graph;

    std::unordered_map<Token*, QVector<double> > inventory_quantities;
    std::unordered_map<Token*, QCPGraph*> token_to_graph;
    PoolInterface *pool_;
    QVector<double> epochs;

    Token *plottedToken1 = nullptr;
    Token *plottedToken2 = nullptr;

    bool plotting_inventory = false;
};

#endif // POOLGRAPHITEM_H
