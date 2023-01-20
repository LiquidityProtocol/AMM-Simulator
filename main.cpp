

#include "QtWidgets/qlabel.h"
#include "introductorywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IntroductoryWindow introw;
    introw.show();

    return a.exec();
}
