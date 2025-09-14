#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

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

    // 转换到HSV色彩空间
    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);

    // 定义红色的HSV阈值范围（红色在HSV中有两个范围）
    Scalar lower_red1(0, 100, 100);
    Scalar upper_red1(10, 255, 255);
    Scalar lower_red2(160, 100, 100);
    Scalar upper_red2(179, 255, 255);

    // 创建红色区域的掩码
    Mat mask1, mask2, redMask;
    inRange(hsvImage, lower_red1, upper_red1, mask1);
    inRange(hsvImage, lower_red2, upper_red2, mask2);
    bitwise_or(mask1, mask2, redMask);

    // 显示原始图像和红色掩码
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    namedWindow("Red Mask", WINDOW_AUTOSIZE);
    imshow("Original Image", image);
    imshow("Red Mask", redMask);

    // 等待按键后关闭窗口
    cout << "按任意键关闭窗口..." << endl;
    waitKey(0);
    destroyAllWindows();

    return 0;
}
