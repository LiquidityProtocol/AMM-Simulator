#include "AccountListWidgetItem.h"
#include "ui_AccountListWidgetItem.h"
#include "MintDialog.h"
#include "WalletListWidgetItem.h"
#include "PoolTokenListWidgetItem.h"
#include <QMessageBox>
#include "MainWindow.h"

AccountListWidgetItem::AccountListWidgetItem(QWidget *parent, Playground *playground, Account *account) :
    QWidget(parent),
    ui(new Ui::AccountListWidgetItem),
    account_(account),
    playground_(playground)
{
    ui->setupUi(this);
    connect(this, &AccountListWidgetItem::UpdatePoolDisplayRequest, qobject_cast<MainWindow *>(parent), &MainWindow::VerifyUpdatePoolDisplayRequest);
    connect(this, &AccountListWidgetItem::UpdateAccountsWalletsRequest, qobject_cast<MainWindow *>(parent), &MainWindow::VerifyUpdateAccountsWalletsRequest);
    ui->lineEdit->setText(QString::fromStdString(account_->name()));
    UpdateWallet();
}

AccountListWidgetItem::~AccountListWidgetItem()
{
    delete ui;
}

Account *AccountListWidgetItem::account() const
{
    return account_;
}

void AccountListWidgetItem::on_mint_pushButton_clicked()
{
    if (!playground_->existing_tokens().size()) {
        QMessageBox::about(this, "Mint failed", "There are no tokens at the moment!");
        return;
    }
    mint_dialog = new MintDialog(this, playground_);
    mint_dialog->setWindowTitle(QString::fromStdString("Mint to account " + account_->name()));
    mint_dialog->exec();
}

void AccountListWidgetItem::on_trade_pushButton_clicked()
{
    trade_dialog = new TradeDialog(this, playground_, account_);
    trade_dialog->setWindowTitle(QString::fromStdString("Trade for account " + account_->name()));
    trade_dialog->exec();
}

void AccountListWidgetItem::on_provide_pushButton_clicked()
{
    provide_dialog = new ProvideDialog(this);
    provide_dialog->setWindowTitle(QString::fromStdString("Provide from account " + account_->name()));
    provide_dialog->exec();
}

void AccountListWidgetItem::on_withdraw_pushButton_clicked()
{
    withdraw_dialog = new WithdrawDialog(this, playground_, account_);
    withdraw_dialog->setWindowTitle(QString::fromStdString("Withdraw from account " + account_->name()));
    withdraw_dialog->exec();
}

void AccountListWidgetItem::UpdateWallet()
{
    ui->lineEdit_2->setText(QString::number(account_->total_value()));
    ui->listWidget->clear();
    for (auto [token, quantity] : account_->wallet()) {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        if (token->pool()) {
            PoolTokenListWidgetItem *pool_token_item = new PoolTokenListWidgetItem(this, token, quantity);
            item->setSizeHint(pool_token_item->sizeHint());
            ui->listWidget->setItemWidget(item, pool_token_item);
        } else {
            WalletListWidgetItem *wallet_item = new WalletListWidgetItem(this, token, quantity);
            item->setSizeHint(wallet_item->sizeHint());
            ui->listWidget->setItemWidget(item, wallet_item);
        }
    }
}

void AccountListWidgetItem::VerifyMintRequest(Token *token, double quantity)
{
    try {
        account_->Deposit(token, quantity);
        UpdateWallet();
        mint_dialog->accept();
    } catch (std::exception &e) {
        QMessageBox::about(mint_dialog, "Mint failed", e.what());
    }
}

void AccountListWidgetItem::VerifyTradeRequest(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) {
    try {
        double curr_slippage = pool->GetSlippage(input_token, output_token, input_quantity);
        playground_->ExecuteSwap(account_, pool, input_token, output_token, input_quantity);
        emit UpdateAccountsWalletsRequest();
        emit UpdatePoolDisplayRequest(pool, curr_slippage);
        trade_dialog->accept();
    } catch (std::exception &e) {
        QMessageBox::about(trade_dialog, "Trade failed", e.what());
    }
}

void AccountListWidgetItem::VerifyWithdrawRequest(Token *input_token, double surrendered_quantity) {
    try {
        playground_->ExecuteWithdrawal(account_, input_token, surrendered_quantity);
        UpdateWallet();
        emit UpdatePoolDisplayRequest(input_token->pool());
        withdraw_dialog->accept();
    } catch (std::exception &e) {
        QMessageBox::about(withdraw_dialog, "Withdraw failed", e.what());
    }
}

void AccountListWidgetItem::VerifyProvisionTypeDeclaration(bool initial_provision)
{
    provide_dialog->accept();
    if (initial_provision) {
        new_pool_provision_dialog = new NewPoolProvisionDialog(this, playground_);
        new_pool_provision_dialog->setWindowTitle(QString::fromStdString("Provide from account " + account_->name()));
        new_pool_provision_dialog->exec();
    } else {
        existing_pool_provision_dialog = new ExistingPoolProvisionDialog(this, playground_);
        existing_pool_provision_dialog->setWindowTitle(QString::fromStdString("Provide from account " + account_->name()));
        existing_pool_provision_dialog->exec();
    }
}

void AccountListWidgetItem::VerifyProvideRequest1(PROTOCOL protocol, const std::unordered_map<Token *, double> &quantities, double pool_fee)
{
    try {
        playground_->ExecuteInitialProvision(account_, protocol, quantities, pool_fee);
        UpdateWallet();
        emit UpdatePoolDisplayRequest(playground_->GetPool(protocol, GetKeys(quantities)));
        new_pool_provision_dialog->accept();
    }  catch (std::exception &e) {
        QMessageBox::about(new_pool_provision_dialog, "Provide failed", e.what());
    }
}

void AccountListWidgetItem::VerifyProvideRequest2(PROTOCOL protocol, const std::unordered_map<Token *, double> &quantities, double pool_fee, double slippage_controller)
{
    try {
        playground_->ExecuteInitialProvision(account_, protocol, quantities, pool_fee, slippage_controller);
        UpdateWallet();
        emit UpdatePoolDisplayRequest(playground_->GetPool(protocol, GetKeys(quantities)));
        new_pool_provision_dialog->accept();
    }  catch (std::exception &e) {
        QMessageBox::about(new_pool_provision_dialog, "Provide failed", e.what());
    }
}

void AccountListWidgetItem::VerifyProvideRequest3(PROTOCOL protocol, const std::unordered_map<Token *, double> &quantities, double pool_fee, const std::unordered_map<Token *, double> &weights)
{
    try {
        playground_->ExecuteInitialProvision(account_, protocol, quantities, pool_fee, weights);
        UpdateWallet();
        emit UpdatePoolDisplayRequest(playground_->GetPool(protocol, GetKeys(quantities)));
        new_pool_provision_dialog->accept();
    }  catch (std::exception &e) {
        QMessageBox::about(new_pool_provision_dialog, "Provide failed", e.what());
    }
}

void AccountListWidgetItem::VerifyExistingProvideRequest(PROTOCOL protocol, const std::unordered_map<Token *, double> &quantities)
{
    try {
        playground_->ExecuteProvision(account_, protocol, quantities);
        UpdateWallet();
        emit UpdatePoolDisplayRequest(playground_->GetPool(protocol, GetKeys(quantities)));
        existing_pool_provision_dialog->accept();
    }  catch (std::exception &e) {
        QMessageBox::about(existing_pool_provision_dialog, "Provide failed", e.what());
    }
}
