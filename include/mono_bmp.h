#include <iostream>
#include <vector>

class MonoBmp
{
private:
    std::string fileName = "test"; 
    const std::string FILE_EXTENSION = ".bmp";
    unsigned char bitsPerPixel = 1;
    std::vector<std::vector<bool>> pixels = {{true, false},{false}};
    int width = 2;
    int height = 2;

    int getRowSize();
public:
    MonoBmp(std::string _name, std::string _path = "../output/");
    ~MonoBmp();
    void save();
    void setPixel(int pixelX,int pixelY, bool colour);

    std::string path; //file path
    unsigned char blackColour[3] = {0,0,0};
    unsigned char whiteColour[3] = {255,255,255};
};