#include "PoolTokenListWidgetItem.h"
#include "ui_PoolTokenListWidgetItem.h"
#include "PoolTokenDialog.h"

PoolTokenListWidgetItem::PoolTokenListWidgetItem(QWidget *parent, Token *token, double quantity) :
    QWidget(parent),
    ui(new Ui::PoolTokenListWidgetItem),
    token_(token),
    quantity_(quantity)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::fromStdString(token_->name()));
}

PoolTokenListWidgetItem::~PoolTokenListWidgetItem()
{
    delete ui;
}

void PoolTokenListWidgetItem::on_pushButton_clicked()
{
    PoolTokenDialog *pool_token_dialog = new PoolTokenDialog(this, token_, quantity_);
    pool_token_dialog->exec();
}
