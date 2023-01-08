#include "MarketInfo.h"
#include "ui_MarketInfo.h"

MarketInfo::MarketInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarketInfo)
{
    ui->setupUi(this);
}

MarketInfo::~MarketInfo()
{
    delete ui;
}
