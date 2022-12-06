#!/bin/bash

SOURCES=$(find Utilities -name '*.cpp')
COMPILER="clang++"

TEST_FILE=$1

# echo ${SOURCES[@]}
# echo $TEST_FILE
$COMPILER -std=c++17 ${SOURCES[@]} $TEST_FILE -o OUT && ./OUT && rm ./OUT

if [ $? -eq 0 ]; then
    echo -e "\033[32mEverything is OK.\033[0m"
# else
#     echo -e "\033[31mSomething is wrong.\033[0m"
fi