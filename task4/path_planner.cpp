#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>

using namespace std;

// 定义坐标点结构
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// 方向：上、右、下、左
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

// 读取地图文件
vector<vector<int>> readMap(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("无法打开地图文件: " + filePath);
    }
    
    vector<vector<int>> map;
    string line;
    
    while (getline(file, line)) {
        vector<int> row;
        size_t pos = 0;
        while ((pos = line.find(' ')) != string::npos) {
            string token = line.substr(0, pos);
            row.push_back(stoi(token));
            line.erase(0, pos + 1);
        }
        if (!line.empty()) {
            row.push_back(stoi(line));
        }
        map.push_back(row);
    }
    
    file.close();
    return map;
}

// 使用BFS寻找路径
vector<Point> findPath(vector<vector<int>>& map, Point start, Point goal) {
    size_t rows = map.size();
    size_t cols = map[0].size();
    
    // 检查起点和终点是否有效
    if (start.x < 0 || start.x >= static_cast<int>(rows) || 
        start.y < 0 || start.y >= static_cast<int>(cols) || 
        map[start.x][start.y] == 1) {
        throw invalid_argument("起点无效或不可通行");
    }
    if (goal.x < 0 || goal.x >= static_cast<int>(rows) || 
        goal.y < 0 || goal.y >= static_cast<int>(cols) || 
        map[goal.x][goal.y] == 1) {
        throw invalid_argument("终点无效或不可通行");
    }
    
    // 创建前驱节点矩阵
    vector<vector<Point>> predecessor(rows, vector<Point>(cols, Point(-1, -1)));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    
    queue<Point> q;
    q.push(start);
    visited[start.x][start.y] = true;
    
    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        
        // 如果到达目标点，回溯路径
        if (current.x == goal.x && current.y == goal.y) {
            vector<Point> path;
            stack<Point> temp;
            Point p = goal;
            
            while (!(p == start)) {
                temp.push(p);
                p = predecessor[p.x][p.y];
            }
            temp.push(start);
            
            while (!temp.empty()) {
                path.push_back(temp.top());
                temp.pop();
            }
            
            return path;
        }
        
        // 探索四个方向
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (nx >= 0 && nx < static_cast<int>(rows) && 
                ny >= 0 && ny < static_cast<int>(cols) && 
                !visited[nx][ny] && map[nx][ny] == 0) {
                visited[nx][ny] = true;
                predecessor[nx][ny] = current;
                q.push(Point(nx, ny));
            }
        }
    }
    
    // 如果没有找到路径
    return vector<Point>();
}

// 打印地图和路径
void printMapWithPath(vector<vector<int>>& map, const vector<Point>& path) {
    // 创建地图副本，将路径标记为2
    vector<vector<int>> mapCopy = map;
    for (const auto& p : path) {
        mapCopy[p.x][p.y] = 2;
    }
    
    // 打印地图
    for (size_t i = 0; i < mapCopy.size(); i++) {
        for (size_t j = 0; j < mapCopy[i].size(); j++) {
            if (mapCopy[i][j] == 0) {
                cout << "0 ";
            } else if (mapCopy[i][j] == 1) {
                cout << "1 ";
            } else {
                cout << "* ";
            }
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        cerr << "用法: " << argv[0] << " <map_file_path> <start_x> <start_y> <goal_x> <goal_y>" << endl;
        return 1;
    }
    
    try {
        // 解析命令行参数
        string mapFilePath = argv[1];
        int startX = stoi(argv[2]);
        int startY = stoi(argv[3]);
        int goalX = stoi(argv[4]);
        int goalY = stoi(argv[5]);
        
        // 读取地图
        vector<vector<int>> map = readMap(mapFilePath);
        
        Point start(startX, startY);
        Point goal(goalX, goalY);
        
        // 寻找路径
        vector<Point> path = findPath(map, start, goal);
        
        if (path.empty()) {
            cout << "I can't go to the postion (" << goalX << "," << goalY << ")." << endl;
        } else {
            printMapWithPath(map, path);
        }
        
    } catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
