#ifndef ACCOUNTLISTWIDGETITEM_H
#define ACCOUNTLISTWIDGETITEM_H

#include <QWidget>
#include "MintDialog.h"
#include "TradeDialog.h"
#include "ProvideDialog.h"
#include "NewPoolProvisionDialog.h"
#include "src/Playground.hpp"

namespace Ui {
class AccountListWidgetItem;
}

class AccountListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit AccountListWidgetItem(QWidget *parent = nullptr, Playground* playground = nullptr, Account *account = nullptr);
    ~AccountListWidgetItem();

public slots:
    void VerifyMintRequest(Token *token, double quantity);
    void VerifyTradeRequest(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity);
    void VerifyProvisionTypeDeclaration(bool initial_provision);

private slots:
    void on_mint_pushButton_clicked();
    void on_trade_pushButton_clicked();
    void on_provide_pushButton_clicked();

private:
    Ui::AccountListWidgetItem *ui;
    Account *account_;
    MintDialog *mint_dialog;
    TradeDialog *trade_dialog;
    ProvideDialog *provide_dialog;
    NewPoolProvisionDialog *new_pool_provision_dialog;
    Playground *playground_;

    void UpdateWallet();
};

#endif // ACCOUNTLISTWIDGETITEM_H
