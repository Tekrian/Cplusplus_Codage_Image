#include "Image.hpp"
GrayImage::GrayImage(uint16_t w, uint16_t h)
    : width(w), height(h), array(nullptr)
{
    if (w == 0 || h == 0)
        throw std::invalid_argument("la largeur et la hauteur doivent etre positives ");

    array = new uint8_t[size_t(width) * height];
}

GrayImage::GrayImage(const GrayImage &orig)
    : width(orig.width), height(orig.height), array(nullptr)
{
    array = new uint8_t[size_t(orig.width) * orig.height];
    for (size_t i = 0; i < (size_t(width) * height); i++)
        array[i] = orig.array[i];
}

GrayImage::~GrayImage()
{
    delete[] array;
}

void GrayImage::clear(uint8_t gray)
{
    size_t taille = size_t(width) * height;
    for (size_t i = 0; i < taille; i++)
        array[i] = gray;
}

void GrayImage::writePGM(std::ostream &os) const
{
    os << "P5\n"
       << "#Image sauvegardée par TETEH Kokou Briand pour les TP de RepCod.\n"
       << width << " " << height << "\n"
       << "255\n";
    os.write((const char *)array, size_t(width) * height);
    if(!os)
        throw std::runtime_error("GrayImage::writePGM : erreur lors de l'écriture");
}

void skip_line(std::istream &is)
{
    char c = ' ';
    while (c != '\n'){
        if(!is.get(c))
            throw std::runtime_error("skip_line : erreur lors de la lecture de la ligne");
    }
}

void skip_comments(std::istream &is)
{
    char c ;
    if(!is.get(c))  // on lit le premier caractère de la ligne
        throw std::runtime_error("skip_comments : erreur lors de la lecture de la ligne");

    while (c == '#') //tant que c'est un commentaire, 
    { 
        skip_line(is); //on saute la ligne
        if(!is.get(c))
            throw std::runtime_error("skip_comments : erreur lors de la lecture de la ligne");
    }
    //on sort de la boucle donc c != #, alors on remet c dans le flux
    is.putback(c);
}

GrayImage* GrayImage::readPGM(std::istream& is){
    //On lit le magic number
    std::string magic_number = " ";
    getline(is, magic_number);
    if(magic_number != "P5")
        throw std::runtime_error("le fichier n'est pas un PGM valide : P5 manque");
    // On saute les éventuels commentaires
    skip_comments(is);
    //lecture de la largeur et de la hauteur
    uint16_t _width, _height;
    if(!(is>>_width>>_height))
        throw std::runtime_error("fichier PGM invalide : largeur/ hauteur incorrextes");
    if(_width == 0 || _height == 0)
        throw std::runtime_error("fichier PGM invalide : largeur/ hauteur nulles (doivent etre positives");
    //on saute /n
    skip_line(is);
    //on saute les éventuels commentaires
    skip_comments(is);
    //lecture de la valeur maximale
    int maxSize = 0;
    if(!(is >> maxSize))
        throw std::runtime_error("fichier PGm invalide : valeur maximale absente");
    if(maxSize != 255)
        throw std::runtime_error("fichier PGM invalide : valeur maximale incorrecte (doit etre 255)");
    //on consomme le linefeeed
    skip_line(is);
    GrayImage * res = new GrayImage(_width, _height);
    is.read((char*) res->array, size_t(_width) * _height);
    if(!is){
        delete res;
        throw std::runtime_error("fichier PGM invalide : données de pixels manquantes");
    }
    return res;
}


// Fonction pour tracer un rectangle
void GrayImage::rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t gray)
{   
    if(w == 0 || h == 0)
        throw std::invalid_argument("GrayImage::rectangle : La largeur et la hauteur du rectangle doivent etre positives");
    if (size_t(x) + w > width || size_t(y) + h > height)
        throw std::out_of_range("GrayImage::rectangle : Le rectangle dépasse les limites de l'image");

    // cotés horizontales
    for (unsigned int i = x; i < unsigned(x) + w; i++)
    {
        pixel(i, y) = gray;
        pixel(i, y + h - 1) = gray;
    }
    // cotés verticales
    for (unsigned int i = y; i < unsigned(y) + h; i++)
    {
        pixel(x, i) = gray;
        pixel(x + w - 1, i) = gray;
    }
}

void GrayImage::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t gray)
{
    if (w == 0 || h == 0)
        throw std::invalid_argument("GrayImage::fillRectangle : La largeur et la hauteur du rectangle doivent etre > 0");

    if (size_t(x) + w > width || size_t(y) + h > height)
        throw std::out_of_range("GrayImage::fillRectangle : Le rectangle dépasse les limites de l'image");
    
    for (uint16_t j = 0; j < h; j++)
        for (uint16_t i = 0; i < w; i++)        
            pixel(x + i, y + j) = gray;
}


bool operator==(const Color& c1, const Color& c2)
{
    return (c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b);
}