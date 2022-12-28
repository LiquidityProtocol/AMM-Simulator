#include "AccountListWidgetItem.h"
#include "ui_AccountListWidgetItem.h"
#include "MintDialog.h"
#include "WalletListWidgetItem.h"
#include <QMessageBox>

AccountListWidgetItem::AccountListWidgetItem(QWidget *parent, Playground *playground, Account *account) :
    QWidget(parent),
    ui(new Ui::AccountListWidgetItem),
    account_(account),
    playground_(playground)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::fromStdString(account_->name()));
    ui->lineEdit_2->setText(QString::number(account_->total_value()));
}

AccountListWidgetItem::~AccountListWidgetItem()
{
    delete ui;
}

void AccountListWidgetItem::VerifyMintRequest(Token *token, double quantity)
{
    try {
        account_->Deposit(token, quantity);
        ui->lineEdit_2->setText(QString::number(account_->total_value()));
        UpdateWallet();
        mint_dialog->accept();
    } catch (std::exception &e) {
        QMessageBox::about(mint_dialog, "Mint failed", e.what());
    }
}

void AccountListWidgetItem::on_mint_pushButton_clicked()
{
    if (!playground_->existing_tokens().size()) {
        QMessageBox::about(this, "Minting failed", "There are no tokens at the moment!");
        return;
    }
    mint_dialog = new MintDialog(this, playground_);
    mint_dialog->exec();
}

void AccountListWidgetItem::on_trade_pushButton_clicked()
{
    trade_dialog = new TradeDialog(this, playground_, account_);
    trade_dialog->exec();
}

void AccountListWidgetItem::UpdateWallet()
{
    ui->listWidget->clear();
    for (auto [token, quantity] : account_->wallet()) {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        WalletListWidgetItem *wallet_item = new WalletListWidgetItem(this, token, quantity);
        item->setSizeHint(wallet_item->sizeHint());
        ui->listWidget->setItemWidget(item, wallet_item);
    }
}

void AccountListWidgetItem::VerifyTradeRequest(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) {
    try {
        playground_->ExecuteSwap(account_, pool, input_token, output_token, input_quantity);
        ui->lineEdit_2->setText(QString::number(account_->total_value()));
        UpdateWallet();
        trade_dialog->accept();
    } catch (std::exception &e) {
        QMessageBox::about(trade_dialog, "Trade failed", e.what());
    }
}

void AccountListWidgetItem::VerifyWithdrawRequest(PoolInterface *pool) {
    try {
        ui->lineEdit_2->setText(QString::number(account_->total_value()));
        UpdateWallet();
        trade_dialog->accept();
    } catch (std::exception &e) {
        QMessageBox::about(trade_dialog, "Trade failed", e.what());
    }
}
