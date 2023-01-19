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
    std::unordered_map<std::string, double> verify_scenario(QString);

private slots:
    void on_runButton_clicked();

    void on_pool_comboBox_currentIndexChanged(int index);
/*
    void on_comboBox_currentIndexChanged(int index2);

    void on_comboBox_2_currentIndexChanged(int index3);
*/
    void on_pushButton_customEpoch_clicked();

    void on_pushButton_load_scenario_clicked();
    void on_View_Options_currentIndexChanged(int index);
    void update_pool_comboBox();

    void on_pushButton_reset_market_clicked();


private:
    Ui::SimulationPlayground *ui;
    Market* market_;
    QVector<double> epochs;
    std::unordered_map<Token*, QVector<double> > inventory_quantities;
    std::unordered_map<Token*, QCPGraph*>token_to_graph;
    Token* test_token;
    CommunityActor *arbitrager;
    CommunityActor *provider;
};

#endif // SIMULATIONPLAYGROUND_H
