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
    explicit ProviderSimulationGraphItem(QWidget *parent = nullptr);
    ~ProviderSimulationGraphItem();

private:
    Ui::ProviderSimulationGraphItem *ui;
};

#endif // PROVIDERSIMULATIONGRAPHITEM_H
