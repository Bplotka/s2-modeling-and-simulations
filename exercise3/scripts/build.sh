#!/usr/bin/env bash
mkdir -p ../build
rm -f ../build/*
LD_LIBRARY_PATH="/usr/local/lib" g++ ../src/exercise3.cpp -o ../build/gites
chmod +x ../build/gites
