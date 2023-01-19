#ifndef ARBITRAGERDIALOG_H
#define ARBITRAGERDIALOG_H
#include <QDialog>

namespace Ui {
class ArbitragerDialog;
}

class ArbitragerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArbitragerDialog(QWidget *parent = nullptr, QVector<double> epochs = {}, QVector<double> wallet_values = {});
    ~ArbitragerDialog();

private:
    Ui::ArbitragerDialog *ui;
};

#endif // ARBITRAGERDIALOG_H
