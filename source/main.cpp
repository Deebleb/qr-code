#include <iostream>
#include <fstream>
#include "../include/mono_bmp.h"

int main(){
    MonoBmp qr = MonoBmp("test");
    qr.path = "C:/Users/howie/Desktop/CodeStuff/C-C++/qr_code/output/";
    qr.save();
    return 0;
}