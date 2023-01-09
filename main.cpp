#include "MainWindow.h"
#include "introductorywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    IntroductoryWindow w;
    w.show();
    return a.exec();
}
