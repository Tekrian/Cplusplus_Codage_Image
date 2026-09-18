#ifndef _GRAYIMAGE_
#define _GRAYIMAGE_
#include <cstdint>

class GrayImage
{
private:
    uint16_t width;
    uint16_t height;
    uint8_t *array; //Pointeur vers le tab alloué dynamiquement des pixels

public:
    GrayImage(uint16_t w, uint16_t h);
    GrayImage(const GrayImage&);
    GrayImage() = delete;
    ~GrayImage();

    GrayImage& operator=(const GrayImage&);
};


#endif