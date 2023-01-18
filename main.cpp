#include "QtWidgets/qlabel.h"
#include "introductorywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IntroductoryWindow w;
    w.show();

    return a.exec();
}
