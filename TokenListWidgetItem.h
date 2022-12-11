#ifndef TOKENLISTWIDGETITEM_H
#define TOKENLISTWIDGETITEM_H

#include <QWidget>
#include "src/Utilities/Utilities.hpp"

namespace Ui {
class TokenListWidgetItem;
}

class TokenListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit TokenListWidgetItem(QWidget *parent = nullptr, Token *token = nullptr);
    ~TokenListWidgetItem();

private:
    Ui::TokenListWidgetItem *ui;
    Token *token_;
};

#endif // TOKENLISTWIDGETITEM_H
