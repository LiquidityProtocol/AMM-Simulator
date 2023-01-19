#ifndef POOLTOKENLISTWIDGETITEM_H
#define POOLTOKENLISTWIDGETITEM_H

#include <QWidget>
#include "src/Utilities/Utilities.hpp"

namespace Ui {
class PoolTokenListWidgetItem;
}

class PoolTokenListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit PoolTokenListWidgetItem(QWidget *parent = nullptr, Token *token = nullptr, double quantity = 0);
    ~PoolTokenListWidgetItem();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PoolTokenListWidgetItem *ui;
    Token *token_;
    double quantity_;
};

#endif // POOLTOKENLISTWIDGETITEM_H
