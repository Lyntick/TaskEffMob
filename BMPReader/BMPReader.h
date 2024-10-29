#ifndef TESTTASKEFFMOB_BMPREADER_H
#define TESTTASKEFFMOB_BMPREADER_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <climits>

// Структура для заголовка файла BMP
#pragma pack(push, 2) // Отключаем выравнивание для структур
struct BMPFileHeader {
    uint16_t bfType;       // Тип файла, должен быть "BM" (0x4D42)
    uint32_t bfSize;       // Размер файла
    uint16_t bfReserved1;  // Зарезервировано
    uint16_t bfReserved2;  // Зарезервировано
    uint32_t bfOffBits;    // Смещение до начала пиксельных данных
};

// Структура для заголовка изображения BMP
struct BMPInfoHeader {
    uint32_t biSize;           // Размер этой структуры (40 байт)
    int32_t  biWidth;          // Ширина изображения
    int32_t  biHeight;         // Высота изображения
    uint16_t biPlanes;         // Число плоскостей (всегда 1)
    uint16_t biBitCount;       // Количество бит на пиксель (24 или 32)
    uint32_t biCompression;    // Тип сжатия (0 = без сжатия)
    uint32_t biSizeImage;      // Размер изображения (в байтах)
    int32_t  biXPelsPerMeter;  // Горизонтальное разрешение (пикселей на метр)
    int32_t  biYPelsPerMeter;  // Вертикальное разрешение (пикселей на метр)
    uint32_t biClrUsed;        // Количество использованных цветов (0 = все)
    uint32_t biClrImportant;   // Количество важных цветов (0 = все)
};
#pragma pack(pop)


class BMPReader{
public:
    BMPReader() = default;
    BMPReader(const BMPReader&) = delete;// copy constructor
    ~BMPReader();

    bool openBMP(const std::string&);//and read
    void displayBMP() const;
    void closeBMP();
private:
    BMPFileHeader bmpHeader;
    BMPInfoHeader bmpInfoHead;
    std::vector<char> pixelGrid;

    std::ifstream fileBMP;
};



#endif //TESTTASKEFFMOB_BMPREADER_H
