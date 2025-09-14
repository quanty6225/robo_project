#!/bin/bash

mkdir -p build
cd build

cmake ..
make

./red_detector ../test_red_armor.jpg
