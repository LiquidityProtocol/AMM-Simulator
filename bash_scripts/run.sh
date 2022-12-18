#!/bin/bash

SOURCES=find ./../src/Utilities/ -name '*.cpp'
COMPILER="clang++"

TEST_FILE=$1

# echo ${SOURCES[@]}
# echo $TEST_FILE
eval "$COMPILER -std=c++17 ${SOURCES[@]} $TEST_FILE -o OUT && ./OUT && rm ./OUT"
echo -e "\033[32mEvething is OK.\033[0m"