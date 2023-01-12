#ifndef WITHDRAWDIALOG_H
#define WITHDRAWDIALOG_H

#include <QDialog>
#include "src/Playground.hpp"

namespace Ui {
class WithdrawDialog;
}

class WithdrawDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WithdrawDialog(QWidget *parent = nullptr, Playground *playground = nullptr, Account *account = nullptr);
    ~WithdrawDialog();

signals:
    void WithdrawRequest(Token *input_token, double surrendered_quantity);

private slots:
    void on_comboBox_protocol_activated(int index);
    void on_comboBox_pool_activated(int index);
    void on_lineEdit_withdraw_textChanged(const QString &text);
    void on_pushButton_withdraw_clicked();

private:
    Ui::WithdrawDialog *ui;
    Playground *playground_;
    Account *account_;
};

#endif // WITHDRAWDIALOG_H
