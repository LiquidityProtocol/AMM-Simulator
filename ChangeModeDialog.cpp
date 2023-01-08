#include "ChangeModeDialog.h"
#include "ui_ChangeModeDialog.h"
#include "SimulationPlayground.h"

ChangeModeDialog::ChangeModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeModeDialog)
{
    ui->setupUi(this);
}

ChangeModeDialog::~ChangeModeDialog()
{
    delete ui;
}

void ChangeModeDialog::on_buttonBox_accepted()
{
    SimulationPlayground* sim_playground = new SimulationPlayground;
    sim_playground->exec();
}

