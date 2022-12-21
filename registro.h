#ifndef PROJETO_PRATICO_REGISTRO_H
#define PROJETO_PRATICO_REGISTRO_H

#include <fstream>
#include <iostream>

using namespace std;

struct Registro {
    char anzsic06[10];
    char Area[10];
    int year;
    int geo_count;
    int ec_count;
    bool gravaBin(ofstream& bin);
    void depura(int id);
};

#endif //PROJETO_PRATICO_REGISTRO_H
