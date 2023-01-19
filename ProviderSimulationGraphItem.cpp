#include "ProviderSimulationGraphItem.h"
#include "ui_ProviderSimulationGraphItem.h"

ProviderSimulationGraphItem::ProviderSimulationGraphItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProviderSimulationGraphItem)
{
    ui->setupUi(this);
}

ProviderSimulationGraphItem::~ProviderSimulationGraphItem()
{
    delete ui;
}
