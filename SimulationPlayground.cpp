#include "SimulationPlayground.h"
#include "ui_SimulationPlayground.h"

SimulationPlayground::SimulationPlayground(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationPlayground)
{
    ui->setupUi(this);
}

SimulationPlayground::~SimulationPlayground()
{
    delete ui;
}
