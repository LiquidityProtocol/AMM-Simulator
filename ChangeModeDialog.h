#ifndef CHANGEMODEDIALOG_H
#define CHANGEMODEDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeModeDialog;
}

class ChangeModeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeModeDialog(QWidget *parent = nullptr);
    ~ChangeModeDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ChangeModeDialog *ui;
};

#endif // CHANGEMODEDIALOG_H
