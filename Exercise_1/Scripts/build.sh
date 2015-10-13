#!/usr/bin/env bash
mkdir -p ../Build
rm -f ../Build/*
LD_LIBRARY_PATH="/usr/local/lib" g++ ../Src/exercise1.cpp -lgmp -lgmpxx -o ../Build/gites
chmod +x ../Build/gites
