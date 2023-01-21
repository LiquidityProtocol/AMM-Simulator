#include "TokenListWidgetItem.h"
#include "ui_TokenListWidgetItem.h"

TokenListWidgetItem::TokenListWidgetItem(QWidget *parent, Token *token) :
    QWidget(parent),
    ui(new Ui::TokenListWidgetItem),
    token_(token)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::fromStdString(token_->name()));
    ui->lineEdit_2->setText(QString::number(token_->real_value()));
}

TokenListWidgetItem::~TokenListWidgetItem()
{
    delete ui;
}

Token *TokenListWidgetItem::token() const {
    return token_;
}
