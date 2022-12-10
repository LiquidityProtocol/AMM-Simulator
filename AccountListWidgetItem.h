#ifndef ACCOUNTLISTWIDGETITEM_H
#define ACCOUNTLISTWIDGETITEM_H

#include <QWidget>
#include "src/Utilities/Utilities.hpp"

namespace Ui {
class AccountListWidgetItem;
}

class AccountListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit AccountListWidgetItem(QWidget *parent = nullptr, Account *account = nullptr);
    ~AccountListWidgetItem();

private:
    Ui::AccountListWidgetItem *ui;
    Account *account_;
};

#endif // ACCOUNTLISTWIDGETITEM_H
