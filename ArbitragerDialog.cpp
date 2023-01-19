#include "ArbitragerDialog.h"
#include "ui_ArbitragerDialog.h"

ArbitragerDialog::ArbitragerDialog(QWidget *parent, QVector<double> epochs, QVector<double> wallet_values) :
    QWidget(parent),
    ui(new Ui::ArbitragerDialog)
{
    ui->setupUi(this);
}

ArbitragerDialog::~ArbitragerDialog()
{
    delete ui;
}
