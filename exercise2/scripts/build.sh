#!/usr/bin/env bash
mkdir -p ../build
rm -f ../build/*
LD_LIBRARY_PATH="/usr/local/lib" g++ ../src/exercise2.cpp -lgmp -lgmpxx -o ../build/gites
chmod +x ../build/gites
