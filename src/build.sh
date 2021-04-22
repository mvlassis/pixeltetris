#!/bin/sh

cmake -S . -B ../build
cmake --build ../build
../build/PixelTetris.out > ../build/log.txt

