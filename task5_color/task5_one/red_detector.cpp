#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

    Mat image = imread(argv[1]);
    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);

    Scalar lower_red1(0, 100, 100);
    Scalar upper_red1(10, 255, 255);
    Scalar lower_red2(160, 100, 100);
    Scalar upper_red2(179, 255, 255);

    Mat mask1, mask2, redMask;
    inRange(hsvImage, lower_red1, upper_red1, mask1);
    inRange(hsvImage, lower_red2, upper_red2, mask2);
    bitwise_or(mask1, mask2, redMask);

    namedWindow("Original Image", WINDOW_AUTOSIZE);
    namedWindow("Red Mask", WINDOW_AUTOSIZE);
    imshow("Original Image", image);
    imshow("Red Mask", redMask);

    cout << "按任意键关闭窗口..." << endl;
    waitKey(0);
    destroyAllWindows();

    return 0;
}
