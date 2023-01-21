#ifndef PROVIDERSIMULATIONGRAPHITEM_H
#define PROVIDERSIMULATIONGRAPHITEM_H

#include <QWidget>
#include "qcustomplot.h"
#include "./src/Market/Agents/Provider.hpp"

namespace Ui {
class ProviderSimulationGraphItem;
}

class ProviderSimulationGraphItem : public QWidget
{
    Q_OBJECT

public:
    explicit ProviderSimulationGraphItem(QWidget *parent = nullptr, PoolInterface *pool = nullptr, Provider *provider = nullptr);
    ~ProviderSimulationGraphItem();

    void clearData();
    void UpdateGraph();


private:
    Ui::ProviderSimulationGraphItem *ui;

    PoolInterface *pool_;
    Provider *provider_;

    int plotted_Epochs = 20;
};

#endif // PROVIDERSIMULATIONGRAPHITEM_H
