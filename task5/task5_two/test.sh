#!/bin/bash

# 创建构建目录
mkdir -p build
cd build

# 使用CMake构建项目
cmake ..
make

# 运行程序
./rune_detector ../test_rune.png
