#ifndef INTRODUCTORYWINDOW_H
#define INTRODUCTORYWINDOW_H

#include <QMainWindow>
#include "NewMainWindow.h"
namespace Ui {
class IntroductoryWindow;
}

class IntroductoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IntroductoryWindow(QWidget *parent = nullptr);
    ~IntroductoryWindow();

private slots:
    void on_pushButton_clicked();    

private:
    Ui::IntroductoryWindow *ui;
    NewMainWindow* mainwindow;
};


#endif // INTRODUCTORYWINDOW_H
