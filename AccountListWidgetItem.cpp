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

void AccountListWidgetItem::VerifyData(Token *token, double quantity)
{
    account_->Deposit(token, quantity);
    ui->lineEdit_2->setText(QString::number(account_->total_value()));
    if(!(account_->GetQuantity(token) - quantity)){
        CreateNewWalletItem(token);
    }else{
        UpdateWalletItem(token);
    }
    mint_dialog->accept();
}

void AccountListWidgetItem::CreateNewWalletItem(Token* token){
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    ui->listWidget->addItem(item);
    WalletListWidgetItem *wallet_item = new WalletListWidgetItem(this, token, account_->GetQuantity(token));
    item->setSizeHint(wallet_item->sizeHint());
    ui->listWidget->setItemWidget(item, wallet_item);
}

void AccountListWidgetItem::UpdateWalletItem(Token* token){
    for(int i = 0; i < ui->listWidget->count(); i++){
        QListWidgetItem* item = ui->listWidget->item(i);
        WalletListWidgetItem* wallet_item = qobject_cast<WalletListWidgetItem*>(ui->listWidget->itemWidget(item));
        if(wallet_item->GetTokenName() == token->name()){
            wallet_item->UpdateTokenQuantity(account_->GetQuantity(token));
        }
        ui->listWidget->setItemWidget(item, wallet_item);
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

