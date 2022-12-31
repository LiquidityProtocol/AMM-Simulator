#ifndef NEWPOOLPROVISIONDIALOG_H
#define NEWPOOLPROVISIONDIALOG_H

#include <QDialog>
#include "src/Playground.hpp"
#include <QComboBox>

namespace Ui {
class NewPoolProvisionDialog;
}

class NewPoolProvisionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPoolProvisionDialog(QWidget *parent = nullptr, Playground *playground = nullptr);
    ~NewPoolProvisionDialog();

signals:
    void ProvideRequest1(PROTOCOL protocol, std::unordered_map<Token *, double> quantities, double pool_fee);
    void ProvideRequest2(PROTOCOL protocol, std::unordered_map<Token *, double> quantities, double pool_fee, double slippage_controller);
    void ProvideRequest3(PROTOCOL protocol, std::unordered_map<Token *, double> quantities, double pool_fee, std::unordered_map<Token *, double> weights);
    void NewProvideRequestPoolUpdate(PROTOCOL protocol, std::unordered_set<Token *> tokens);

private slots:
    void on_comboBox_protocol_activated(int index);
    void on_tableWidget_tokens_rowClicked(int row);
    void on_pushButton_provide_clicked();

private:
    Ui::NewPoolProvisionDialog *ui;
    Playground *playground_;
    std::vector<QComboBox *> comboBoxes_tokens_;
    std::vector<QLineEdit *> lineEdits_quantities_, lineEdits_weights_;
};

#endif // NEWPOOLPROVISIONDIALOG_H
