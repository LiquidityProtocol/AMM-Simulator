#ifndef POOLTOKENDIALOG_H
#define POOLTOKENDIALOG_H

#include <QDialog>
#include "src/Utilities/Utilities.hpp"

namespace Ui {
class PoolTokenDialog;
}

class PoolTokenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PoolTokenDialog(QWidget *parent = nullptr, Token *token = nullptr, double quantity = 0);
    ~PoolTokenDialog();

private:
    Ui::PoolTokenDialog *ui;
};

#endif // POOLTOKENDIALOG_H
