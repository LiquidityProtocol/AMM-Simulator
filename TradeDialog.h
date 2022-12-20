#ifndef TRADEDIALOG_H
#define TRADEDIALOG_H

#include <QDialog>
#include "src/Playground.hpp"

namespace Ui {
class TradeDialog;
}

class TradeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TradeDialog(QWidget *parent = nullptr, Playground* playground=nullptr, Account* account_=nullptr);
    ~TradeDialog();

private slots:
    void on_input_token_comboBox_currentTextChanged(const QString &arg1);

    void on_output_token_comboBox_currentTextChanged(const QString &arg1);

    void on_protocol_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::TradeDialog *ui;
    Playground *playground_;
    Account* account_;
};

#endif // TRADEDIALOG_H
