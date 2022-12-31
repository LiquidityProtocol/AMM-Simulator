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
    connect(this, &AccountListWidgetItem::AddPoolInfo, qobject_cast<MainWindow *>(parent), &MainWindow::VerifyAddPoolInfo);
    ui->lineEdit->setText(QString::fromStdString(account_->name()));
    ui->lineEdit_2->setText(QString::number(account_->total_value()));
}

AccountListWidgetItem::~AccountListWidgetItem()
{
    delete ui;
}

Account *AccountListWidgetItem::account() const
{
    return account_;
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

void AccountListWidgetItem::VerifyProvisionTypeDeclaration(bool initial_provision)
{
    provide_dialog->accept();
    if (initial_provision) {
        new_pool_provision_dialog = new NewPoolProvisionDialog(this, playground_);
        new_pool_provision_dialog->exec();
    } else {
        existing_pool_provision_dialog = new ExistingPoolProvisionDialog(this, playground_);
        existing_pool_provision_dialog->exec();
    }
}

void AccountListWidgetItem::VerifyProvideRequest1(PROTOCOL protocol, std::unordered_map<Token *, double> quantities, double pool_fee)
{
    try {
        playground_->ExecuteInitialProvision(account_, protocol, quantities, pool_fee);
        ui->lineEdit_2->setText(QString::number(account_->total_value()));
        UpdateWallet();

        std::unordered_set<Token *> tokens;
        for ( auto [token, quantity] : quantities) {
            tokens.emplace(token);
        }
        PoolInterface *curr_pool = playground_->GetPool(protocol, tokens);
        new_pool_provision_dialog->accept();
    }  catch (std::exception &e) {
        QMessageBox::about(new_pool_provision_dialog, "Provide failed", e.what());
    }
}

void AccountListWidgetItem::VerifyProvideRequest2(PROTOCOL protocol, std::unordered_map<Token *, double> quantities, double pool_fee, double slippage_controller)
{
    try {
        playground_->ExecuteInitialProvision(account_, protocol, quantities, pool_fee, slippage_controller);
        ui->lineEdit_2->setText(QString::number(account_->total_value()));
        UpdateWallet();
        new_pool_provision_dialog->accept();
    }  catch (std::exception &e) {
        QMessageBox::about(new_pool_provision_dialog, "Provide failed", e.what());
    }
}

void AccountListWidgetItem::VerifyProvideRequest3(PROTOCOL protocol, std::unordered_map<Token *, double> quantities, double pool_fee, std::unordered_map<Token *, double> weights)
{
    try {
        playground_->ExecuteInitialProvision(account_, protocol, quantities, pool_fee, weights);
        ui->lineEdit_2->setText(QString::number(account_->total_value()));
        UpdateWallet();
        new_pool_provision_dialog->accept();
    }  catch (std::exception &e) {
        QMessageBox::about(new_pool_provision_dialog, "Provide failed", e.what());
    }
}

void AccountListWidgetItem::VerifyExistingProvideRequest(PROTOCOL protocol, std::unordered_map<Token *, double> provided_quantities)
{
    try {
        playground_->ExecuteProvision(account_, protocol, provided_quantities);
        ui->lineEdit_2->setText(QString::number(account_->total_value()));
        UpdateWallet();
        existing_pool_provision_dialog->accept();
    }  catch (std::exception &e) {
        QMessageBox::about(existing_pool_provision_dialog, "Provide failed", e.what());
    }
}

void AccountListWidgetItem::on_provide_pushButton_clicked()
{
    provide_dialog = new ProvideDialog(this);
    provide_dialog->exec();
}
