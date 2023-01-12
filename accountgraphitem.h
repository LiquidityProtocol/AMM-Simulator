#ifndef ACCOUNTGRAPHITEM_H
#define ACCOUNTGRAPHITEM_H

#include "qcustomplot.h"
#include "src/Utilities/Utilities.hpp"
#include <QWidget>

namespace Ui {
class accountgraphitem;
}

class accountgraphitem : public QWidget
{
    Q_OBJECT

public:
    explicit accountgraphitem(QWidget *parent = nullptr, Account *account=nullptr);
    ~accountgraphitem();

    void UpdateGraph();

private:
    Ui::accountgraphitem *ui;

    std::unordered_map<Token*, std::unordered_map<Token*, QCPGraph*> > pToken_to_graph;
    std::unordered_map<Token*, QCPGraph*> token_to_graph;

    Account *account_ = nullptr;

    bool plotting_inventory = true;
};

#endif // ACCOUNTGRAPHITEM_H
