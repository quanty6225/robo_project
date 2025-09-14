#!/bin/bash

# 创建构建目录
mkdir -p build
cd build

# 使用CMake构建项目
cmake ..
make

# 运行程序
./red_detector ../test_red_armor.jpg
