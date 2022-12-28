#ifndef ACCOUNTLISTWIDGETITEM_H
#define ACCOUNTLISTWIDGETITEM_H

#include <QWidget>
#include "src/Utilities/Utilities.hpp"
#include "MintDialog.h"
#include "src/Playground.hpp"
#include "TradeDialog.h"
#include "withdrawDialog.h"

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
    void VerifyWithdrawRequest(Token *input_token, double surrendered_quantity);

private slots:
    void on_mint_pushButton_clicked();
    void on_trade_pushButton_clicked();
    void on_withdraw_pushButton_clicked();

private:
    Ui::AccountListWidgetItem *ui;
    Account *account_;
    MintDialog *mint_dialog;
    TradeDialog *trade_dialog;
    WithdrawDialog *withdraw_dialog;
    Playground *playground_;

    void UpdateWallet();
};

#endif // ACCOUNTLISTWIDGETITEM_H
