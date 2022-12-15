#include "MainWindow.h"
#include "graphwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    GraphWindow x;
    x.show();
    return a.exec();
}
