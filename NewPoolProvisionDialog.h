#ifndef NEWPOOLPROVISIONDIALOG_H
#define NEWPOOLPROVISIONDIALOG_H

#include <QDialog>

namespace Ui {
class NewPoolProvisionDialog;
}

class NewPoolProvisionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPoolProvisionDialog(QWidget *parent = nullptr);
    ~NewPoolProvisionDialog();

private slots:
    void on_comboBox_protocol_activated(int index);

    void on_tableWidget_tokens_cellClicked(int row, int column);

private:
    Ui::NewPoolProvisionDialog *ui;
};

#endif // NEWPOOLPROVISIONDIALOG_H
