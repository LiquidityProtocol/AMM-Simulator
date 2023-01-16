#ifndef PROVIDEDIALOG_H
#define PROVIDEDIALOG_H

#include <QDialog>

namespace Ui {
class ProvideDialog;
}

class ProvideDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProvideDialog(QWidget *parent = nullptr);
    ~ProvideDialog();

signals:
    void ProvisionTypeDeclaration(bool initial_provision);

private slots:
    void on_pushButton_newPool_clicked();
    void on_pushButton_existingPool_clicked();

private:
    Ui::ProvideDialog *ui;
};

#endif // PROVIDEDIALOG_H
