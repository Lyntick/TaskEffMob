
#include "BMPReader.h"


BMPReader::~BMPReader() {
    closeBMP();
}


bool BMPReader::openBMP(const std::string &fileName) {
    fileBMP.open(fileName, std::ios_base::binary);
    if(!fileBMP.is_open()){
        std::cerr << "The file doesn't open!" << std::endl;
        return false;
    }
    fileBMP.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
    fileBMP.read(reinterpret_cast<char*>(&bmpInfoHead), sizeof(bmpInfoHead));

    if(bmpInfoHead.biBitCount != 24 && bmpInfoHead.biBitCount != 32){  //read check for 24 or 32 bit image
        std::cerr << "Support only 24 or 32 bit image!" << std::endl;
        closeBMP();
        return false;
    }

    if(bmpInfoHead.biCompression != 0){
        std::cerr << "Doesn't support any compression!" << std::endl;
        closeBMP();
        return false;
    }

    //todo read pixels
    // think about padding
    int width = bmpInfoHead.biWidth;
    int height = abs(bmpInfoHead.biHeight);
    int padding = (width * (bmpInfoHead.biBitCount / 8)) % 4;
    pixelGrid.resize(width*height);


    fileBMP.seekg(bmpHeader.bfOffBits, std::ios::beg);// go to pixel data
    for(int i = 0;  i < height * width; ++i){
        unsigned char bgr[3];
        fileBMP.read(reinterpret_cast<char*>(bgr), 3); //read 3 byte b g r

        if (bgr[0] == 0 && bgr[1] == 0 && bgr[2] == 0) {
            pixelGrid[i] = '#';  // black
        } else if (bgr[0] == 255 && bgr[1] == 255 && bgr[2] == 255) {
            pixelGrid[i] = '.';  // white
        } else {
            std::cerr << "Найден неподдерживаемый цвет в изображении!" << std::endl;
            return false;
        }

        if(i % width == 0){//ignoring padding
            fileBMP.ignore(padding);
        }
    }
    if(bmpInfoHead.biHeight > 0){
        std::reverse(pixelGrid.begin(), pixelGrid.end());
    }

    return true;
}


void BMPReader::displayBMP() const {
    int width = bmpInfoHead.biWidth;
    int height = abs(bmpInfoHead.biHeight);
    for(int i = 0; i <  height * width; ++i){
        if(i % width == 0){
            std::cout << '\n';
        }
        std::cout << pixelGrid[i];
    }
}


void BMPReader::closeBMP() {
    if(fileBMP.is_open()){
        fileBMP.close();
    }
    if(!pixelGrid.empty()){
        pixelGrid.clear();
    }
}


