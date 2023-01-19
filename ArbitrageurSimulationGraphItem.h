#ifndef ARBITRAGEURSIMULATIONGRAPHITEM_H
#define ARBITRAGEURSIMULATIONGRAPHITEM_H

#include <QWidget>

namespace Ui {
class ArbitrageurSimulationGraphItem;
}

class ArbitrageurSimulationGraphItem : public QWidget
{
    Q_OBJECT

public:
    explicit ArbitrageurSimulationGraphItem(QWidget *parent = nullptr);
    ~ArbitrageurSimulationGraphItem();

private:
    Ui::ArbitrageurSimulationGraphItem *ui;
};

#endif // ARBITRAGEURSIMULATIONGRAPHITEM_H
