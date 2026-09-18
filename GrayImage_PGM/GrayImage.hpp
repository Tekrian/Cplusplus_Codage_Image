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

    //Accesseurrs de consultation de la largeur/ hauteur
    inline const uint16_t& getWidth() const { return width;};
    inline const uint16_t& getHeight() const {return height;};
    //Accesseurrs de modification des pixel
    inline uint8_t& pixel(uint16_t x, uint16_t y) {return array[y*width + x];};
    //Accesseur de consultation des pixels
    inline const uint8_t& pixel(uint16_t  x, uint16_t y) const {return array[y*width + x];};
    GrayImage& operator=(const GrayImage&);
};


#endif