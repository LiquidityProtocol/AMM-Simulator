#include "AccountListWidgetItem.h"
#include "ui_AccountListWidgetItem.h"

AccountListWidgetItem::AccountListWidgetItem(QWidget *parent, Account *account) :
    QWidget(parent),
    ui(new Ui::AccountListWidgetItem),
    account_(account)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::fromStdString(account_->name()));
    ui->lineEdit_2->setText(QString::number(account_->total_value()));
}

AccountListWidgetItem::~AccountListWidgetItem()
{
    delete ui;
}
