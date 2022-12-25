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

private slots:

    void on_create_toekn_pushButton_clicked();

    void on_create_account_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Playground *playground_;
};
#endif // MAINWINDOW_H
