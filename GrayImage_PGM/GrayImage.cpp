#include "GrayImage.hpp"
GrayImage::GrayImage(uint16_t w, uint16_t h)
    : width(w), height(h)
{

}

GrayImage::GrayImage(const GrayImage& orig)
    : width(orig.width), height(orig.height)
{

}

GrayImage::~GrayImage(){
    
}