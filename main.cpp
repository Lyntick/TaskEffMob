#include <string>
#include <iostream>

#include "BMPReader/BMPReader.h"

using namespace std;

// Главная функция программы
int main(int argc, char* argv[]) {


    if (argc != 2) {
        cerr << "Warning: drawBmp.exe <path to BMP file>" << endl;
        return 1;
    }

    string fileName = argv[1];

    BMPReader bmp;
    bmp.openBMP(fileName);
    bmp.displayBMP();


    return 0;
}
