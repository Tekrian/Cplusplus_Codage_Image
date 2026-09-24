#include "GrayImage.hpp"
GrayImage::GrayImage(uint16_t w, uint16_t h)
    : width(w), height(h), array(nullptr)
{
    array = new uint8_t[width*height];
}

GrayImage::GrayImage(const GrayImage& orig)
    : width(orig.width), height(orig.height), array(nullptr)
{
    array = new uint8_t [orig.width * orig.height];
    for(size_t i = 0; i < (width*height); i++)
        array[i] = orig.array[i];
}

GrayImage::~GrayImage(){
    delete [] array;
}

void GrayImage::writePGM(std::ostream& os) const{
    os << "P5\n"
       << "#Image sauvegardée par TETEH Kokou Briand pour les TP de RepCod.\n"
       << width << " " << height
       <<"\n"
       <<"255\n";
       os.write((const char*)array, width*height);
}

void skip_line(std::istream& is){
    char c = ' ';
    while(c != '\n')
        is.get(c);
}