#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    // Leer la imagen a color
    Mat colorImage = imread("imagenacolor.jpg", IMREAD_COLOR);

    // Crear una matriz vacía del mismo tamaño para la imagen en escala de grises
    Mat grayImage(colorImage.rows, colorImage.cols, CV_8UC1);

    // Procesar cada píxel
    for (int r = 0; r < colorImage.rows; r++) {
        for (int c = 0; c < colorImage.cols; c++) {
            Vec3b pixel = colorImage.at<Vec3b>(r, c);

            // Convertir a escala de grises utilizando el promedio
            uchar grayValue = (pixel[0] + pixel[1] + pixel[2]) / 3;

            grayImage.at<uchar>(r, c) = grayValue;
        }
    }

    // Guardar la imagen en escala de grises
    imwrite("imagenengrises.jpg", grayImage);

    return 0;
}
