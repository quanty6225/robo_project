#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

double calculateCircularity(const vector<Point>& contour) {
    double area = contourArea(contour);
    double perimeter = arcLength(contour, true);
    
    if (perimeter == 0) return 0;
    
    return (4 * M_PI * area) / (perimeter * perimeter);
}

int main(int argc, char** argv) {
    Mat gray;
    Mat image = imread(argv[1]);
    cvtColor(image, gray, COLOR_BGR2GRAY);
    Mat binary;
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    double maxCircularity = 0;
    int bestContourIdx = -1;
    Rect bestBoundingRect;
    
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        
        if (area < 1000) continue;
        
        double circularity = calculateCircularity(contours[i]);
        
        cout << "轮廓 " << i << ": 面积=" << area << ", 圆度=" << circularity << endl;
        
        if (circularity > maxCircularity && circularity > 0.7) {
            maxCircularity = circularity;
            bestContourIdx = i;
            bestBoundingRect = boundingRect(contours[i]); 
        }
    }

    if (bestContourIdx != -1) {
        rectangle(image, bestBoundingRect, Scalar(0, 255, 0), 2);
        
        string circularityText = "Circularity: " + to_string(maxCircularity);
        putText(image, circularityText, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
        
        cout << "找到圆形轮廓，圆度: " << maxCircularity << endl;
        cout << "边界框坐标: x=" << bestBoundingRect.x << ", y=" << bestBoundingRect.y 
             << ", width=" << bestBoundingRect.width << ", height=" << bestBoundingRect.height << endl;
    } else {
        cout << "未找到符合条件的圆形轮廓" << endl;
        putText(image, "No circle found", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
    }

    namedWindow("Original Image", WINDOW_AUTOSIZE);
    namedWindow("Binary Image", WINDOW_AUTOSIZE);
    imshow("Original Image", image);
    imshow("Binary Image", binary);

    cout << "按任意键关闭窗口..." << endl;
    waitKey(0);
    destroyAllWindows();

    return 0;
}    
