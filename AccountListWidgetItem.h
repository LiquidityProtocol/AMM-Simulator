#ifndef ACCOUNTLISTWIDGETITEM_H
#define ACCOUNTLISTWIDGETITEM_H

#include <QWidget>
#include "src/Utilities/Utilities.hpp"
#include "MintDialog.h"
#include "ProvideDialog.h"
#include <QtCharts/QChart>

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
    void Graph(QWidget* parent);

public slots:
    void VerifyData(Token *token, double quantity);
 //   void VerifyPool(Token *token1, Token *token2, std::string protocol);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::AccountListWidgetItem *ui;
    Account *account_;
    MintDialog *mint_dialog;
    ProvideDialog *provide_dialog;

};

#endif // ACCOUNTLISTWIDGETITEM_H
