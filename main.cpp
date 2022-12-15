#include "MainWindow.h"
#include <QApplication>
#include "src/Utilities/FirstSimulation.hpp"
//#include <src/Utilities/FirstSimulation.hpp>
#include "src/Protocols/UniswapV2Pool.hpp"
// #include <conio.h>
#include "src/Utilities/UniswapV2PoolSimulation.hpp"



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    SimulationOne();
    UniswapV2PoolTest1();
    UniswapV2PoolTest2();
    UniswapV2PoolTest3();
    MainWindow w;
    w.show();
    return a.exec();

};
