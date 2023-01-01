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
    void ExistingProvideRequest(PROTOCOL protocol, std::unordered_map<Token *, double> input_quantities);

private slots:
    void on_comboBox_pool_activated(int index);

    void on_pushButton_provide_clicked();

    void on_lineEdit_input_token_textChanged(const QString &input_text);

private:
    Ui::ExistingPoolProvisionDialog *ui;
    Playground *playground_;
};
#endif // EXISTINGPOOLPROVISIONDIALOG_H
