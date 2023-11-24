#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat image = imread("imagenacolor.jpg", IMREAD_COLOR);

    // read each pixel (RGB pixel)
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            Point3_<uchar>* p = image.ptr<Point3_<uchar>>(r, c);
            // X: B, Y: G, Z: R
            printf("(%d %d %d) ", p->x, p->y, p->z);
        }
    }

    return 0;
}
