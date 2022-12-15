#include "MainWindow.h"

#include <QApplication>
#include "src/Utilities/FirstSimulation.hpp"
//#include <src/Utilities/FirstSimulation.hpp>
#include <iostream>
#include <conio.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    SimulationOne();
    MainWindow w;
    w.show();
    return a.exec();
}
