#ifndef MINTDIALOG_H
#define MINTDIALOG_H

#include <QDialog>
#include "src/Utilities/Utilities.hpp"

namespace Ui {
class MintDialog;
}

class MintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MintDialog(QWidget *parent = nullptr);
    ~MintDialog();

signals:
    void SendData(Token *token, double quantity);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MintDialog *ui;
};

#endif // MINTDIALOG_H
