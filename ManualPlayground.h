#ifndef MANUALPLAYGROUND_H
#define MANUALPLAYGROUND_H

#include <QWidget>
#include "src/Playground.hpp"

namespace Ui {
class ManualPlayground;
}

class ManualPlayground : public QWidget
{
    Q_OBJECT

public:
    explicit ManualPlayground(QWidget *parent = nullptr);
    ~ManualPlayground();

public slots:
    void VerifyUpdatePoolDisplayRequest(PoolInterface *pool);

private slots:
    void on_create_toekn_pushButton_clicked();
    void on_create_account_pushButton_clicked();

private:
    Ui::ManualPlayground *ui;
    Playground *playground_;
};

#endif // MANUALPLAYGROUND_H
