#ifndef PROVIDERSIMULATIONGRAPHITEM_H
#define PROVIDERSIMULATIONGRAPHITEM_H

#include <QWidget>

namespace Ui {
class ProviderSimulationGraphItem;
}

class ProviderSimulationGraphItem : public QWidget
{
    Q_OBJECT

public:
    explicit ProviderSimulationGraphItem(QWidget *parent = nullptr, PoolInterface *pool = nullptr);
    ~ProviderSimulationGraphItem();

    void clearData();
    void UpdateGraph();


private:
    Ui::ProviderSimulationGraphItem *ui;

    PoolInterface *pool_;

    QCPGraph *line1;
    QCPGraph *line2;

    Provider *provider = nullptr;

    int plotted_Epochs = 20;
};

#endif // PROVIDERSIMULATIONGRAPHITEM_H
