#ifndef WALLETLISTWIDGETITEM_H
#define WALLETLISTWIDGETITEM_H
#include "src/Utilities/Utilities.hpp"
#include <QWidget>

namespace Ui {
class WalletListWidgetItem;
}

class WalletListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit WalletListWidgetItem(QWidget *parent = nullptr, Token *token = nullptr, double quantity = 0);
    ~WalletListWidgetItem();

private:
    Ui::WalletListWidgetItem *ui;
};

#endif // WALLETLISTWIDGETITEM_H
