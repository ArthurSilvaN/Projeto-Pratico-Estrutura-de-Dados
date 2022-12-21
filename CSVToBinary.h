#ifndef PROJETO_PRATICO_CSVTOBINARY_H
#define PROJETO_PRATICO_CSVTOBINARY_H


#include <iostream>
#include <string>
#include "registro.h"

using namespace std;

class CSVToBinary {
public:
    string arq_csv;
    string arq_bin;
    //-2 por conta do cabeçalho e a posicao relativa começar em 1
    unsigned quantidadeDados = -2;
    CSVToBinary(string arq_csv, string arq_bin);
    ~CSVToBinary();
    void testeArquivoBinario();
private:
    Registro registro{};
    void setRegistro(ifstream& csv);
    void *parseChar(string source, char *characters);
};

#endif //PROJETO_PRATICO_CSVTOBINARY_H
