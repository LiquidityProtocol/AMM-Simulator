#ifndef ACCOUNTLISTWIDGETITEM_H
#define ACCOUNTLISTWIDGETITEM_H

#include <QWidget>
#include "src/Utilities/Utilities.hpp"
#include "MintDialog.h"
#include "src/Playground.hpp"
#include "TradeDialog.h"
#include "Withdraw.h"

namespace Ui {
class AccountListWidgetItem;
}

class AccountListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit AccountListWidgetItem(QWidget *parent = nullptr, Playground* playground = nullptr, Account *account = nullptr);
    ~AccountListWidgetItem();
    void CreateNewWalletItem(Token* token);
    void UpdateWalletItem(Token* token);

public slots:
    void VerifyData(Token *token, double quantity);

private slots:
    void on_mint_pushButton_clicked();

    void on_trade_pushButton_clicked();

    void on_withdraw_pushButton_clicked();

private:
    Ui::AccountListWidgetItem *ui;
    Account *account_;
    MintDialog *mint_dialog;
    TradeDialog *trade_dialog;
    Withdraw *withdraw;
    Playground *playground_;
};

#endif // ACCOUNTLISTWIDGETITEM_H
