#!/bin/bash

mkdir -p build
cd build

cmake ..
make

./rune_detector ../test_rune.png
