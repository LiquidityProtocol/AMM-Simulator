#ifndef SIMULATIONPLAYGROUND_H
#define SIMULATIONPLAYGROUND_H

#include <QDialog>
#include "src/Market/Infrastructure/Market.hpp"
#include <qcustomplot.h>

namespace Ui {
class SimulationPlayground;
}

class SimulationPlayground : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationPlayground(QWidget *parent = nullptr);
    ~SimulationPlayground();
    void UpdateGraph(PoolInterface *pool);

private slots:
    void on_pushButton_clicked();

    void on_pool_comboBox_currentIndexChanged(int index);

    void on_pushButton_customEpoch_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SimulationPlayground *ui;
    Market* market_;
    QVector<double> epochs;
    std::unordered_map<Token*, QVector<double> > inventory_quantities;
    std::unordered_map<Token*, QCPGraph*>token_to_graph;
    Token* test_token;
};

#endif // SIMULATIONPLAYGROUND_H
