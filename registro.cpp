/*
 * registro.cpp -> implementação das funções da estrutura de Registro
 *
 * GAC108 - Estruturas de Dados
 * by Arthur Nunes, Caio Bastos e Pedro Rabelo 2022
 *
 */
#include "registro.h"

//metodo para imprimir o Registro
void Registro::depura(int id) {
    cout << "[" << id << ": "
         << anzsic06 << " - "
         << Area << " - "
         << year << " - "
         << geo_count << " - "
         << ec_count << "]"
         << endl;
}

//metodo para gravar Registro no arquivo binario
bool Registro::gravaBin(ofstream& bin){
    if(!bin.good()) return false;
    bin.write((const char *) this, sizeof(Registro));
    return true;
}