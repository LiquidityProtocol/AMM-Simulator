#ifndef SIMULATIONPLAYGROUND_H
#define SIMULATIONPLAYGROUND_H

#include <QDialog>

namespace Ui {
class SimulationPlayground;
}

class SimulationPlayground : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationPlayground(QWidget *parent = nullptr);
    ~SimulationPlayground();

private:
    Ui::SimulationPlayground *ui;
};

#endif // SIMULATIONPLAYGROUND_H
