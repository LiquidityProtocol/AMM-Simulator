#include "ArbitragerDialog.h"
#include "ui_ArbitragerDialog.h"

ArbitragerDialog::ArbitragerDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArbitragerDialog)
{
    ui->setupUi(this);
}

ArbitragerDialog::~ArbitragerDialog()
{
    delete ui;
}
