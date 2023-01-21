#ifndef EXISTINGPOOLPROVISIONDIALOG_H
#define EXISTINGPOOLPROVISIONDIALOG_H

#include <QDialog>
#include "src/Playground.hpp"

namespace Ui {
class ExistingPoolProvisionDialog;
}

class ExistingPoolProvisionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExistingPoolProvisionDialog(QWidget *parent = nullptr, Playground *playground = nullptr);
    ~ExistingPoolProvisionDialog();

signals:
    void ExistingProvideRequest(PROTOCOL protocol, const std::unordered_map<Token *, double> &quantities);

private slots:
    void on_comboBox_protocol_activated(int index);
    void on_comboBox_pool_activated(int index);
    void on_comboBox_input_token_activated(int index);
    void on_lineEdit_input_token_textChanged(const QString &input_token_provision_text);
    void on_pushButton_provide_clicked();

private:
    Ui::ExistingPoolProvisionDialog *ui;
    Playground *playground_;

    void UpdateProvision();
};

#endif // EXISTINGPOOLPROVISIONDIALOG_H
