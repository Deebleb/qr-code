#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../include/mono_bmp.h"

//Thanks to wikipedia: https://en.wikipedia.org/wiki/BMP_file_format and this video: https://www.youtube.com/watch?v=vqT5j38bWGg

MonoBmp::MonoBmp(std::string _name, int _width, int _height, std::string _path)
: fileName(_name),width(_width), height(_height), path(_path){
    //resizes the vector to have all the pixels to avoid trying to access out of the vector
    pixels.resize(height);
    for(int i = 0; i < height; i++){
        pixels[i].resize(width);
    }
}

MonoBmp::~MonoBmp(){}

void MonoBmp::setPixel(int pixelX, int pixelY, bool colour){
    if(pixelY < height && pixelX < width){
        pixels[pixelY][pixelX] = colour;
    }
    else{
        std::cout << "pixel set is not withing image boundaries";
    }
}

int MonoBmp::getRowSize(){ //size of pixel row in bytes
    return ((bitsPerPixel * width + 31)/32) *4;
}

void MonoBmp::save(){
    //open files
    std::ofstream of;
    of.open(path + fileName + FILE_EXTENSION, std::ofstream::trunc);
    std::cout << path + fileName + FILE_EXTENSION;
    if(!of.is_open()){
        std::cout << "File failed to open\n";
        return;
    }

    const unsigned char FILE_HEADER_SIZE = 14;
    const unsigned char INFORMATION_HEADER_SIZE = 40; //Windows BITMAPINFOHEADER size
    unsigned int fileSize = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + 8 + (getRowSize() * abs(height)); //headers + colour table + pixels
    unsigned int pixelOffset = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + 8; //headers and colour table


    unsigned char fileHeader[FILE_HEADER_SIZE] =
    {
        //file format
        'B',
        'M',
        //shift bits to write int onto characters | int is 32 bits, char is 8 bits
        fileSize,      
        fileSize >> 8,
        fileSize >> 16,
        fileSize >> 24,
        //reserved bytes
        0,
        0,
        0,
        0,
        pixelOffset,
        pixelOffset >> 8,
        pixelOffset >> 16,
        pixelOffset >> 24
    };

    unsigned char informationHeader[INFORMATION_HEADER_SIZE] =
    {       
        //DIB header: Windows BITMAPINFOHEADER
        INFORMATION_HEADER_SIZE,
        INFORMATION_HEADER_SIZE >> 8,
        INFORMATION_HEADER_SIZE >> 16,
        INFORMATION_HEADER_SIZE >> 24,
        width,
        width >> 8,
        width >> 16,
        width >> 24,
        height,
        height >> 8,
        height >> 16,
        height >> 24,
        //planes must be 1
        1,
        0,
        //bits per pixel
        bitsPerPixel,
        0,
        //compression: BI_RGB - none
        0,
        0,
        0,
        0,
        //image size: 0 for BI_RGB
        0,
        0,
        0,
        0,
        //horizontal pixels per metre (unspecified)
        0,
        0,
        0,
        0,
        //vertical pixels per metre (unspecified)
        0,
        0,
        0,
        0,
        //colour palette (not used)
        0,
        0,
        0,
        0,
        //important colours, generally ignored
        0,
        0,
        0,
        0,
    };

    unsigned char colourTable[8] = //4 per 2 colours , idk why its backwards :/ thats probably just how it is
    {
        //white (0)
        whiteColour[0],
        whiteColour[1],
        whiteColour[2],
        0x00,

        //black (1)
        blackColour[0],
        blackColour[1],
        blackColour[2],
        0x00
    };

    of.write(reinterpret_cast<char*>(fileHeader),FILE_HEADER_SIZE); //needs to be a char* https://cplusplus.com/reference/ostream/ostream/write/
    std::cout << "File header written to file\n";
    of.write(reinterpret_cast<char*>(informationHeader),INFORMATION_HEADER_SIZE);
    std::cout << "Information header written to file\n";
    of.write(reinterpret_cast<char*>(colourTable), 8);
    std::cout << "Colour table  written to file\n";

    for(int i = 0; i < height;i++){ //each row
        for(int j = 0; j<getRowSize(); j++){ //each byte in row

            //write a byte
            unsigned char byte =0; //byte with no data
            for(int k = 0;k < 8;k++){
                byte *= 2; //push last bit along

                if(j*8 + k < width){ //check if pixel is within the image's width otherwise it is padding (so 0)
                    if(!pixels[i].capacity() <= j*8 + k)
                        byte += pixels[i][j*8 + k];
                }
                //if bit is padding leave the byte the same (writing a 0)
            }
        of << byte; //write byte to file
        }
    }

    of.close();
}
