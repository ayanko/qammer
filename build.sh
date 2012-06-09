#!/bin/bash
set -e
rm -rf build
mkdir build
cd build
qmake ..
make
mkdir -p ../bin
cp qammer ../bin/
