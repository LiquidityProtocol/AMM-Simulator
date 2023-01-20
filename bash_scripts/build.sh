#!/bin/sh

rm -rf build
mkdir build
cd build
qmake ../LiquidityProtocol.pro
make -j4
