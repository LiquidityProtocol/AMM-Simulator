#include "introductionwindow.h"
#include "MainWindow.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "ui_introductionwindow.h"
#include <QPushButton>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>

IntroductionWindow::IntroductionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IntroductionWindow)
{
    ui->setupUi(this);
}

IntroductionWindow::~IntroductionWindow()
{
    delete ui;
}

void IntroductionWindow::on_pushButton_ContinuetoPlayground_clicked() {
{
    MainWindow w;
    w.show();
     }

}
/*
int main() {

    QPushButton *button = new QPushButton("ContinueToPlayground");




QLabel* label = new QLabel(this);
label->setText("Hello, World!");
label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

QVBoxLayout* layout = new QVBoxLayout(this);
layout->addWidget(label);

}
*/
