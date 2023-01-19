#include "ArbitrageurSimulationGraphItem.h"
#include "ui_ArbitrageurSimulationGraphItem.h"

ArbitrageurSimulationGraphItem::ArbitrageurSimulationGraphItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArbitrageurSimulationGraphItem)
{
    ui->setupUi(this);
}

ArbitrageurSimulationGraphItem::~ArbitrageurSimulationGraphItem()
{
    delete ui;
}
