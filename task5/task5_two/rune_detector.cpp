#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

// 计算轮廓的圆度
double calculateCircularity(const vector<Point>& contour) {
    double area = contourArea(contour);
    double perimeter = arcLength(contour, true);
    
    if (perimeter == 0) return 0;
    
    // 圆度 = 4π * 面积 / 周长²
    // 对于完美圆形，这个值接近1
    return (4 * M_PI * area) / (perimeter * perimeter);
}

int main(int argc, char** argv) {
    // 检查命令行参数
    if (argc != 2) {
        cout << "使用方法: " << argv[0] << " <图片路径>" << endl;
        return -1;
    }

    // 读取图像
    Mat image = imread(argv[1]);
    if (image.empty()) {
        cout << "错误：无法加载图像，请检查文件路径" << endl;
        return -1;
    }

    // 转换为灰度图
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // 二值化处理
    Mat binary;
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // 查找轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // 筛选最可能的圆形轮廓
    double maxCircularity = 0;
    int bestContourIdx = -1;
    Rect bestBoundingRect;
    
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        
        // 过滤掉太小的轮廓
        if (area < 1000) continue;
        
        double circularity = calculateCircularity(contours[i]);
        
        cout << "轮廓 " << i << ": 面积=" << area << ", 圆度=" << circularity << endl;
        
        // 寻找圆度最高的轮廓
        if (circularity > maxCircularity && circularity > 0.7) {
            maxCircularity = circularity;
            bestContourIdx = i;
            bestBoundingRect = boundingRect(contours[i]); // 正确调用 boundingRect 函数
        }
    }

    // 在原图上标记最可能的圆形轮廓
    if (bestContourIdx != -1) {
        rectangle(image, bestBoundingRect, Scalar(0, 255, 0), 2);
        
        // 显示圆度信息
        string circularityText = "Circularity: " + to_string(maxCircularity);
        putText(image, circularityText, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
        
        cout << "找到圆形轮廓，圆度: " << maxCircularity << endl;
        cout << "边界框坐标: x=" << bestBoundingRect.x << ", y=" << bestBoundingRect.y 
             << ", width=" << bestBoundingRect.width << ", height=" << bestBoundingRect.height << endl;
    } else {
        cout << "未找到符合条件的圆形轮廓" << endl;
        putText(image, "No circle found", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
    }

    // 显示结果
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    namedWindow("Binary Image", WINDOW_AUTOSIZE);
    imshow("Original Image", image);
    imshow("Binary Image", binary);

    // 等待按键后关闭窗口
    cout << "按任意键关闭窗口..." << endl;
    waitKey(0);
    destroyAllWindows();

    return 0;
}    
