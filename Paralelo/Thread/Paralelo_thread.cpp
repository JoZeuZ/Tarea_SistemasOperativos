#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <vector>

using namespace cv;
using namespace std;
using namespace std::chrono;

void convertToGrayscale(const Mat& input, Mat& output, int startRow, int endRow) {
    for (int r = startRow; r < endRow; r++) {
        for (int c = 0; c < input.cols; c++) {
            Vec3b pixel = input.at<Vec3b>(r, c);
            uchar grayValue = (pixel[0] + pixel[1] + pixel[2]) / 3;
            output.at<uchar>(r, c) = grayValue;
        }
    }
}

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

    vector<thread> threads;
    int rowsPerThread = colorImage.rows / numThreads;

    cout << "Start conversion . . ." << endl;
    auto start = high_resolution_clock::now();

    for (int i = 0; i < numThreads; i++) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? colorImage.rows : (i + 1) * rowsPerThread;
        threads.emplace_back(convertToGrayscale, cref(colorImage), ref(grayImage), startRow, endRow);
    }

    for (auto& th : threads) {
        th.join();
    }

    auto stop = high_resolution_clock::now();
    cout << "End conversion . . ." << endl;

    imwrite(argv[2], grayImage);

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Total time spent in seconds is " << duration.count() / 1000000.0 << endl;

    return 0;
}
