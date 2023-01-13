#include "introductorywindow.h"
#include "ui_introductorywindow.h"
#include "MainWindow.h"

IntroductoryWindow::IntroductoryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IntroductoryWindow)
{
    ui->setupUi(this);
}

IntroductoryWindow::~IntroductoryWindow()
{
    delete ui;
}

void IntroductoryWindow::on_pushButton_clicked()
{
    this->close();
    mainwindow = new MainWindow(this);
    mainwindow -> show();

}

