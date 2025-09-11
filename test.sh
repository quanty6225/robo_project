#!/bin/bash

echo "开始测试任务2的工具..."

# 进入工具目录
cd task2_tools

# 检查是否需要编译
if [ -f "hello_robo.cpp" ]; then
    echo "编译C++程序..."
    g++ -o hello_robo hello_robo.cpp
    
    if [ $? -eq 0 ]; then
        echo "编译成功！"
        echo "运行程序："
        ./hello_robo
    else
        echo "编译失败！"
        exit 1
    fi
else
    echo "未找到C++源文件"
    exit 1
fi

echo "测试完成！"
