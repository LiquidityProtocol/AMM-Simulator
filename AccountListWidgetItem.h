#ifndef ACCOUNTLISTWIDGETITEM_H
#define ACCOUNTLISTWIDGETITEM_H

#include <QWidget>
#include "src/Utilities/Utilities.hpp"
#include "MintDialog.h"

namespace Ui {
class AccountListWidgetItem;
}

class AccountListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit AccountListWidgetItem(QWidget *parent = nullptr, Account *account = nullptr);
    ~AccountListWidgetItem();
    void CreateNewWalletItem(Token* token);
    void UpdateWalletItem(Token* token);

public slots:
    void VerifyData(Token *token, double quantity);

private slots:
    void on_pushButton_clicked();

private:
    Ui::AccountListWidgetItem *ui;
    Account *account_;
    MintDialog *mint_dialog;
};

#endif // ACCOUNTLISTWIDGETITEM_H
