#!/bin/sh
CURRENT_DIR=$(pwd)
wget https://gmplib.org/download/gmp/gmp-6.0.0a.tar.xz
tar xf gmp-6.0.0a.tar.xz
cd gmp-6.0.0 && ./configure --enable-cxx --prefix=$CURRENT_DIR --disable-shared && make && make install
