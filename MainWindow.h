#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/Playground.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void VerifyUpdatePoolDisplayRequest(PoolInterface *pool);
    void VerifyUpdatePoolDisplayRequest2(PoolInterface *pool, std::unordered_map<Token *, double> last_quants, std::unordered_map<Token *, std::unordered_map<Token *, double>> last_spots);

private slots:
    void on_create_toekn_pushButton_clicked();
    void on_create_account_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Playground *playground_;
};

#endif // MAINWINDOW_H
