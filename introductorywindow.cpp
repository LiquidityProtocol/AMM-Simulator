#include "introductorywindow.h"
#include "ui_introductorywindow.h"
#include "MainWindow.h"
#include  <QPixmap>

IntroductoryWindow::IntroductoryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IntroductoryWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/jasmine/Desktop/LP_logo.png");
    //int w = ui->label_pic->width();
    //int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(50,50,Qt::KeepAspectRatio));
}

IntroductoryWindow::~IntroductoryWindow()
{
    delete ui;
}

void IntroductoryWindow::on_pushButton_clicked()
{
    mainwindow = new MainWindow(this);
    //mainwindow -> setModal(true);
    mainwindow -> show();
}

