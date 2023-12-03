#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <omp.h>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida> <num_threads>" << endl;
        return 1;
    }

    Mat colorImage = imread(argv[1], IMREAD_COLOR);
    if (colorImage.empty()) {
        cerr << "Error al cargar la imagen: " << argv[1] << endl;
        return 1;
    }

    cout << "Loading image . . ." << endl;
    cout << "Rows (height): " << colorImage.rows << " Cols (width): " << colorImage.cols << endl;

    Mat grayImage(colorImage.rows, colorImage.cols, CV_8UC1);
    int numThreads = stoi(argv[3]);

    cout << "Start conversion . . ." << endl;
    auto start = high_resolution_clock::now();

    #pragma omp parallel for num_threads(numThreads) collapse(2)
    for (int r = 0; r < colorImage.rows; r++) {
        for (int c = 0; c < colorImage.cols; c++) {
            Vec3b pixel = colorImage.at<Vec3b>(r, c);
            uchar grayValue = (pixel[0] + pixel[1] + pixel[2]) / 3;
            grayImage.at<uchar>(r, c) = grayValue;
        }
    }

    auto stop = high_resolution_clock::now();
    cout << "End conversion . . ." << endl;

    imwrite(argv[2], grayImage);

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Total time spent in seconds is " << duration.count() / 1000000.0 << endl;

    return 0;
}
