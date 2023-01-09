#include "MainWindow.h"
#include "introductionwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    IntroductionWindow w;
    w.show();
    return a.exec();
}
