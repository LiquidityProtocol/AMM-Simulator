#!/bin/sh

rm -rf build
mkdir build
cd build
qmake ../src/LiquidityProtocol.pro
make -j4
