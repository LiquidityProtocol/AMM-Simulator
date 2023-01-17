#ifndef ACCOUNTGRAPHITEM_H
#define ACCOUNTGRAPHITEM_H

#include "qcustomplot.h"
#include "src/Utilities/Utilities.hpp"
#include <QWidget>

namespace Ui {
class AccountGraphItem;
}

class AccountGraphItem : public QWidget
{
    Q_OBJECT

public:
    explicit AccountGraphItem(QWidget *parent = nullptr, Account *account=nullptr);
    ~AccountGraphItem();

    void UpdateGraph();

private:
    Ui::AccountGraphItem *ui;
    std::unordered_map<Account*, std::unordered_map<Account*, QCPGraph*> > pAccount_to_graph;
    std::unordered_map<Account*, QCPGraph*> account_to_graph;

    Account *account_;
    QVector<double> *epochs;
    QVector<double> *wallet_values;

};

#endif // ACCOUNTGRAPHITEM_H
