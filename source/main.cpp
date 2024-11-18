#include <iostream>
#include <fstream>
#include "../include/mono_bmp.h"

int main(){
    MonoBmp qr = MonoBmp("test");
    qr.pixels = {true, false, false, true};
    qr.save();
    return 0;
}