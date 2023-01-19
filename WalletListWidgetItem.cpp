#include "WalletListWidgetItem.h"
#include "ui_WalletListWidgetItem.h"

WalletListWidgetItem::WalletListWidgetItem(QWidget *parent, Token *token, double quantity) :
    QWidget(parent),
    ui(new Ui::WalletListWidgetItem)
{
    ui->setupUi(this);
    ui->lineEdit_token->setText(QString::fromStdString(token->name()));
    ui->lineEdit_quantity->setText(QString::number(quantity));
}

WalletListWidgetItem::~WalletListWidgetItem()
{
    delete ui;
}
