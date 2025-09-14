#!/bin/bash

g++ -std=c++11 -Wall -o path_planner path_planner.cpp

echo "运行路径规划测试 (从 (0,0) 到 (1,0))..."
./path_planner "map.txt" 0 0 1 0
echo "运行路径规划测试 (从 (0,0) 到 (2,0))..."
./path_planner "map.txt" 0 0 2 0
echo "运行路径规划测试 (从 (0,0) 到 (3,0))..."
./path_planner "map.txt" 0 0 3 0
echo "运行路径规划测试 (从 (0,0) 到 (0,1))..."
./path_planner "map.txt" 0 0 0 1
echo "运行路径规划测试 (从 (0,0) 到 (0,2))..."
./path_planner "map.txt" 0 0 0 2
echo "运行路径规划测试 (从 (0,0) 到 (1,1))..."
./path_planner "map.txt" 0 0 1 1
echo "运行路径规划测试 (从 (0,0) 到 (4,4))..."
./path_planner "map.txt" 0 0 4 4
echo "运行路径规划测试 (从 (0,0) 到 (0,-1))..."
./path_planner "map.txt" 0 0 0 -1

