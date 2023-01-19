#ifndef ARBITRAGEURSIMULATIONGRAPHITEM_H
#define ARBITRAGEURSIMULATIONGRAPHITEM_H
#include <QDialog>

namespace Ui {
class ArbitrageurSimulationGraphItem;
}

class ArbitrageurSimulationGraphItem : public QWidget
{
    Q_OBJECT

public:
    explicit ArbitrageurSimulationGraphItem(QWidget *parent = nullptr, QVector<double> epochs={0}, QVector<double> wallet_values={0});
    ~ArbitrageurSimulationGraphItem();

private:
    Ui::ArbitrageurSimulationGraphItem *ui;
};

#endif // ARBITRAGEURSIMULATIONGRAPHITEM_H

