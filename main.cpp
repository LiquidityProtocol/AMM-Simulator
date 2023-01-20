#include "NewMainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NewMainWindow w;
    w.show();
    return a.exec();
}
