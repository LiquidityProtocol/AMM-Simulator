#include "PoolTokenDialog.h"
#include "ui_PoolTokenDialog.h"

PoolTokenDialog::PoolTokenDialog(QWidget *parent, Token *token, double quantity) :
    QDialog(parent),
    ui(new Ui::PoolTokenDialog)
{
    ui->setupUi(this);
    ui->lineEdit_share->setText(QString::number(quantity / token->pool()->total_pool_token_quantity() * 100));
    ui->lineEdit_totalValue->setText(QString::number(quantity * token->real_value()));
}

PoolTokenDialog::~PoolTokenDialog()
{
    delete ui;
}
