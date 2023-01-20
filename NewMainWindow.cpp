#include "NewMainWindow.h"
#include "ui_NewMainWindow.h"
#include "SimulationPlayground.h"
#include "ManualPlayground.h"

NewMainWindow::NewMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewMainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->clear();
    ui->tabWidget->addTab(new ManualPlayground, "Manual Playground #1");
    ui->tabWidget->addTab(new SimulationPlayground, "Simulation Playground #1");

}

NewMainWindow::~NewMainWindow()
{
    delete ui;
}


void NewMainWindow::on_pushButton_addManualPlayground_clicked()
{
    manualPlaygroundCount ++;
    ui->tabWidget->addTab(new ManualPlayground, "Manual Playground #" + QString::number(manualPlaygroundCount));
}


void NewMainWindow::on_pushButton_addSimulation_clicked()
{
    simulationPlaygroundCount ++;
    ui->tabWidget->addTab(new SimulationPlayground, "Simulation Playground #" + QString::number(simulationPlaygroundCount));
}


void NewMainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

