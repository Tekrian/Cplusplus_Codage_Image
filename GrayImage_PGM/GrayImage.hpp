#ifndef GRAYIMAGE_HPP
#define GRAYIMAGE_HPP
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <string>

class GrayImage
{
private:
    const uint16_t width;
    const uint16_t height;
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
    inline uint8_t& pixel(uint16_t x, uint16_t y) {
        if(x >= width || y >= height)
            throw std::out_of_range("GrayImage::pixel : un des coordonnée est hors limite");
        return array[size_t(y) * width + x];
    };
    //Accesseur de consultation des pixels
    inline const uint8_t& pixel(uint16_t  x, uint16_t y) const {
        if(x >= width || y >= height)
            throw std::out_of_range("GrayImage::pixel : un des coordonnée est hors limite");
        return array[size_t(y) * width + x];
    };

    GrayImage& operator=(const GrayImage&) = delete;

    void clear(uint8_t gray = 0); // fonction qui éfface l'image( mettre tous les pixels à la valeur gray)

    void writePGM(std::ostream&) const; //méthode qui écrit l'image courante suivant les spécifications PGM en par
    static GrayImage* readPGM(std::istream&); //méthode qui fabrique une nouvelle img à partir des données reçues
    
    
    void rectangle(uint16_t, uint16_t, uint16_t, uint16_t,uint8_t); //fonction qui trace dans l'img un cadre rectangulaire
    
    void fillRectangle(uint16_t, uint16_t, uint16_t, uint16_t,uint8_t); //fonction qui trace un rectangle plein
};
void skip_line(std::istream&); //méthode utiliser pour sauter les lignes
void skip_comments(std::istream&); // méthode qui saute les commentaires)


#endif