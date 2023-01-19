#ifndef ARBITRAGERDIALOG_H
#define ARBITRAGERDIALOG_H

#include <QWidget>

namespace Ui {
class ArbitragerDialog;
}

class ArbitragerDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ArbitragerDialog(QWidget *parent = nullptr);
    ~ArbitragerDialog();

private:
    Ui::ArbitragerDialog *ui;
};

#endif // ARBITRAGERDIALOG_H
