思路：使用findPath函数（BFS）寻找最短路径，再用printMapWithPath函数可视化路径

使用方法：1.test.sh方法：
          修改出发点和结束点需要在test.sh脚本中修改最下面两行对应的数字
          然后bash test.sh或./test.sh都可以
          2.命令行调用方法：
          ./path_planner map.txt x1 y1 x2 y2
          其中（x1，y1）是出发点坐标，（x2，y2）是终止点坐标
