#include "AccountListWidgetItem.h"
#include "ui_AccountListWidgetItem.h"
#include "MintDialog.h"

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

void AccountListWidgetItem::VerifyData(Token *token, double quantity)
{
    account_->Deposit(token, quantity);
    ui->lineEdit_2->setText(QString::number(account_->total_value()));
    mint_dialog->accept();
}

void AccountListWidgetItem::on_pushButton_clicked()
{
    mint_dialog = new MintDialog(this);
    mint_dialog->exec();
}
