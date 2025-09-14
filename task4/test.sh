#!/bin/bash

# 脚本名称: test.sh
# 用途: 编译和运行机器人路径规划程序

# 设置错误处理：任何命令失败则退出脚本
set -e

# 定义变量
PROGRAM_NAME="path_planner"
SOURCE_FILE="path_planner.cpp"

# 编译程序
echo "编译程序..."
g++ -std=c++11 -Wall -o "$PROGRAM_NAME" "$SOURCE_FILE"

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "编译成功！"
else
    echo "编译失败！"
    exit 1
fi

# 检查地图文件是否存在
if [ ! -f "map.txt" ]; then
    echo "创建地图文件 map.txt..."
    cat > map.txt << EOF
0 0 1 1 0
0 1 0 1 0
0 1 0 0 1
1 1 0 1 1
0 0 0 1 0
EOF
    echo "地图文件创建完成。"
fi

# 运行程序测试 (从 (0,0) 到 (4,4))
echo "运行路径规划测试 (从 (0,0) 到 (1,0))..."
./"$PROGRAM_NAME" "map.txt" 0 0 1 0

echo ""
# 运行另一个测试 (从 (0,0) 到 (3,0)) - 应无法到达
echo "运行测试 (从 (0,0) 到 (3,0)) - 应无法到达..."
./"$PROGRAM_NAME" "map.txt" 0 0 3 0
