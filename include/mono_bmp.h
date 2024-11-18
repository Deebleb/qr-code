#include <iostream>
#include <vector>

class MonoBmp
{
private:
    std::string path;
    std::string fileName = "test"; 
    const std::string FILE_EXTENSION = ".bmp";
    unsigned char bitsPerPixel = 1;

    int getRowSize();
public:
    MonoBmp(std::string _name, std::string _path = "../output/");
    ~MonoBmp();
    void save();

    std::vector<bool> pixels;
    int width = 2;
    int height = 2;
    unsigned char blackColour[3] = {0,0,0};
    unsigned char whiteColour[3] = {255,255,255};
};