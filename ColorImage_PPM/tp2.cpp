#include <iostream>
#include <fstream>
#include "Image.hpp"

int main()
{
  try {
    //lecture de chat_petit.ppm
    std::ifstream ifs("chat_petit.ppm", std::ios::binary);
    if (!ifs)
        throw std::runtime_error("impossible d'ouvrir chat_petit.ppm");
    ColorImage* petit = ColorImage::readPPM(ifs);
    std::cout << "lecture du fichier reussie; chat_petit.ppm: " << petit->getWidth() << " x " << petit->getHeight() << std::endl;

    // on agrandit chat_petit.ppm
    ColorImage* simple = petit->simpleScale(823, 400);

    // ecriture de l'img tp2_simple.ppm
    std::ofstream ofs("tp2_simple.ppm", std::ios::binary);
    if(!ofs)
        throw std::runtime_error("impossible de creer tp2_simple.ppm");
    simple->writePPM(ofs);
    std::cout << "tp2_simple.ppm ecrit" << std::endl;

    delete simple;
    delete petit;
  }
  catch (const std::exception& e) {
    std::cerr << "Erreur : " << e.what() << std::endl;
  }
  return 0;
}