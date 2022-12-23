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

//    void on_protocol_comboBox_currentTextChanged(const QString &arg1);

    void on_output_token_comboBox_currentTextChanged(const QString &output_token);

    void on_protocol_comboBox_currentIndexChanged(int index);

    void on_pool_comboBox_currentIndexChanged(int index);

    void on_input_quantity_lineEdit_textChanged(const QString &arg1);

private:
    Ui::TradeDialog *ui;
    Playground *playground_;
    Account* account_;
    PoolInterface* current_pool_;
    Token* input_token_;
    Token* output_token_;
    PROTOCOL protocol_;
};

#endif // TRADEDIALOG_H
