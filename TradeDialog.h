#ifndef TRADEDIALOG_H
#define TRADEDIALOG_H

#include <QDialog>
#include "src/Playground.hpp"

namespace Ui {
class TradeDialog;
}

class Selection {
public:
    PoolInterface *pool_;
    Token *input_token_;
    Token *output_token_;
    double input_quantity_;

    Selection();

    bool Valid() const;
    void Reset();
};

class TradeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TradeDialog(QWidget *parent = nullptr, Playground *playground = nullptr, Account *account = nullptr);
    ~TradeDialog();

signals:
    void TradeRequest(PoolInterface *pool, Token *input_token, Token *output_token, double quantity);

private slots:
    void on_input_token_comboBox_activated(int index);
    void on_output_token_comboBox_activated(int index);
    void on_protocol_comboBox_currentIndexChanged(int index);
    void on_protocol_comboBox_activated(int index);
    void on_pool_comboBox_currentIndexChanged(int index);
    void on_input_quantity_lineEdit_textChanged(const QString &input_quantity_string);
    void on_pushButton_clicked();

private:
    Ui::TradeDialog *ui;
    Playground *playground_;
    Account *account_;
    Selection selection_;

    void UpdateSelection();
    void UpdateOutputQuantity();
};

#endif // TRADEDIALOG_H
