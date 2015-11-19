#!/usr/bin/env bash
mkdir -p ../build
rm -f ../build/*
LD_LIBRARY_PATH="/usr/local/lib" g++ --std=c++11 ../src/exercise3.cpp -o ../build/generator
chmod +x ../build/generator
