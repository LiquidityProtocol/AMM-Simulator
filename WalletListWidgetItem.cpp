#include "WalletListWidgetItem.h"
#include "ui_WalletListWidgetItem.h"

WalletListWidgetItem::WalletListWidgetItem(QWidget *parent, Token* token, double quantity) :
    QWidget(parent),
    ui(new Ui::WalletListWidgetItem),
    token_(token)
{
    ui->setupUi(this);
    ui->lineEdit_token->setText(QString::fromStdString(token->name()));
    ui->lineEdit_quantity->setText(QString::number(quantity));
}

WalletListWidgetItem::~WalletListWidgetItem()
{
    delete ui;
}

std::string WalletListWidgetItem::GetTokenName(){
    return token_->name();
}

Token* WalletListWidgetItem::GetToken(){
    return token_;
}

void WalletListWidgetItem::UpdateTokenQuantity(double quantity){
    ui->lineEdit_quantity->setText(QString::number(quantity));
}
