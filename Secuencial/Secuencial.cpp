#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
    // Verificar que se hayan proporcionado los argumentos correctos
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida>" << endl;
        return 1;
    }

    // Leer la imagen a color
    Mat colorImage = imread(argv[1], IMREAD_COLOR);

    // Verificar si la imagen fue cargada correctamente
    if (colorImage.empty()) {
        cerr << "Error al cargar la imagen: " << argv[1] << endl;
        return 1;
    }

    cout << "Loading image . . ." << endl;
    cout << "Rows (height): " << colorImage.rows << " Cols (width): " << colorImage.cols << endl;

    // Crear una matriz vacía del mismo tamaño para la imagen en escala de grises
    Mat grayImage(colorImage.rows, colorImage.cols, CV_8UC1);

    cout << "Start conversion . . ." << endl;

    auto start = high_resolution_clock::now();

    // Procesar cada píxel
    for (int r = 0; r < colorImage.rows; r++) {
        for (int c = 0; c < colorImage.cols; c++) {
            Vec3b pixel = colorImage.at<Vec3b>(r, c);

            // Convertir a escala de grises utilizando el promedio
            uchar grayValue = (pixel[0] + pixel[1] + pixel[2]) / 3;

            grayImage.at<uchar>(r, c) = grayValue;
        }
    }

    auto stop = high_resolution_clock::now();

    cout << "End conversion . . ." << endl;

    // Guardar la imagen en escala de grises
    imwrite(argv[2], grayImage);

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Total time spent in seconds is " << duration.count() / 1000000.0 << endl;

    return 0;
}
