#ifndef SIMULATIONPLAYGROUND_H
#define SIMULATIONPLAYGROUND_H

#include <QDialog>
#include <qcustomplot.h>

#include "src/Market/Simulation.hpp"

namespace Ui {
class SimulationPlayground;
}

class SimulationPlayground : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationPlayground(QWidget *parent = nullptr);
    ~SimulationPlayground();
    std::unordered_map<std::string, double> verify_scenario(QString);

private slots:
    void on_runButton_clicked();

    void on_pool_comboBox_currentIndexChanged(int index);

    void on_pushButton_customEpoch_clicked();

    void on_pushButton_load_scenario_clicked();
    void on_pushButton_analyze_arbitrager_clicked();
    void on_View_Options_currentIndexChanged(int index);
    void update_pool_comboBox();

    void on_pushButton_reset_market_clicked();


    void on_Arbs_Options_currentIndexChanged(int index);

private:
    Simulation *Sim;

    Ui::SimulationPlayground *ui;
    QVector<double> epochs;
    QVector<double> wallet_values;
    std::unordered_map<Token*, QVector<double> > inventory_quantities;
    std::unordered_map<Token*, QCPGraph*>token_to_graph;
    Token* test_token;
    Arbitrager* arbitrager;
};

#endif // SIMULATIONPLAYGROUND_H
