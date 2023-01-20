#ifndef ARBITRAGEURSIMULATIONGRAPHITEM_H
#define ARBITRAGEURSIMULATIONGRAPHITEM_H
#include <QDialog>

namespace Ui {
class ArbitrageurSimulationGraphItem;
}

class ArbitrageurSimulationGraphItem : public QDialog
{
    Q_OBJECT

public:
    explicit ArbitrageurSimulationGraphItem(QWidget *parent = nullptr, QVector<double> epochs={}, QVector<double> wallet_values={});
    ~ArbitrageurSimulationGraphItem();

private:
    Ui::ArbitrageurSimulationGraphItem *ui;
    QVector<double> epochs;
    QVector<double> wallet_values_;
};

#endif // ARBITRAGEURSIMULATIONGRAPHITEM_H

