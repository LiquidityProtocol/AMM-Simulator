#ifndef MINTDIALOG_H
#define MINTDIALOG_H

#include <QDialog>
#include "src/Utilities/Utilities.hpp"
#include "src/Playground.hpp"

namespace Ui {
class MintDialog;
}

class MintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MintDialog(QWidget *parent = nullptr, Playground *playground = nullptr);
    ~MintDialog();

signals:
    void MintRequest(Token *token, double quantity);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MintDialog *ui;
    Playground *playground_;
};

#endif // MINTDIALOG_H
