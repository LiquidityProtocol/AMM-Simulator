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

private slots:
    void on_pushButton_pool_select_clicked();

private:
    Ui::ExistingPoolProvisionDialog *ui;
    Playground *playground_;
};
#endif // EXISTINGPOOLPROVISIONDIALOG_H
