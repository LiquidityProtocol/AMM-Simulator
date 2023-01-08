#ifndef SIMULATIONPLAYGROUND_H
#define SIMULATIONPLAYGROUND_H

#include <QDialog>
#include "src/Market/Infrastructure/Market.hpp"

namespace Ui {
class SimulationPlayground;
}

class SimulationPlayground : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationPlayground(QWidget *parent = nullptr);
    ~SimulationPlayground();
    void VerifyUpdatePoolDisplayRequest(PoolInterface *pool);

private slots:
    void on_pushButton_clicked();

private:
    Ui::SimulationPlayground *ui;
    Market* market_;

};

#endif // SIMULATIONPLAYGROUND_H
