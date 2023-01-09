#ifndef INTRODUCTIONWINDOW_H
#define INTRODUCTIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class IntroductionWindow;
}

class IntroductionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IntroductionWindow(QWidget *parent = nullptr);
    ~IntroductionWindow();
    void on_pushButton_ContinuetoPlayground_clicked();

private:
    Ui::IntroductionWindow *ui;
};

#endif // INTRODUCTIONWINDOW_H
