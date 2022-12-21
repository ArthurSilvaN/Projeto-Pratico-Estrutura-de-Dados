/*
 * CSVToBinary.cpp -> implementação de metodos para a classe CSVToBinary
 *
 * GAC108 - Estruturas de Dados
 * by Arthur Nunes, Caio Bastos e Pedro Rabelo 2022
 *
 */

#include "CSVToBinary.h"

//metodo para setar um registro
void CSVToBinary::setRegistro(ifstream& csv) {
    string anzsic06, Area, year, geo_count, ec_count;
    getline(csv, anzsic06, ',');
    getline(csv, Area, ',');
    getline(csv, year, ',');
    getline(csv, geo_count, ',');
    getline(csv, ec_count);
    parseChar(anzsic06, registro.anzsic06);
    parseChar(Area, registro.Area);
    registro.year = atoi(year.c_str());
    registro.geo_count = atoi(geo_count.c_str());
    registro.ec_count = atoi(ec_count.c_str());
    quantidadeDados++;
}

CSVToBinary::~CSVToBinary() {}

//metodo para passar string para char para manipular arquivo binário
void * CSVToBinary::parseChar(string source, char *characters) {
    for (int i = 0; i < source.length(); i++) {
        characters[i] = source[i];
    }
    return nullptr;
}

//metodo construtor para realizar a conversão do arquivo csv para binario
CSVToBinary::CSVToBinary(string arquivoCSV, string arquivoBinario) {
    arq_csv = arquivoCSV;
    arq_bin = arquivoBinario;
    ifstream f_csv(arq_csv);
    ifstream bin(arq_bin, ios::out|ios::binary);

    //se o arquivo existe não ira converter os dados novamente
    if(bin) {
        Registro *registroAux = new Registro;
        while (bin.read((char *) registroAux, sizeof(Registro))){
            quantidadeDados++;
        }
    } else {
        ofstream f_bin;
        f_bin.open(arq_bin, ios::out|ios::binary);
        string primeiraLinha;
        getline(f_csv, primeiraLinha);

        cout << "Convertendo dados..." << endl;

        while (f_csv.good()) {
            setRegistro(f_csv);
            if(!registro.gravaBin(f_bin)){
                cout << "Erro ao gravar dado para o arquivo binario" << endl;
            }
        }
        cout << quantidadeDados << " dados convertidos para o arquivo binario " << arq_bin << endl;
        f_csv.close();
        f_bin.close();
    }
}

//metodo para testar diferentes posições absolutas no arquivo binario
void CSVToBinary::testeArquivoBinario(){
    ifstream f_bin;
    f_bin.open(arq_bin, std::ios::binary | std::ios::in);

    cout << "Teste arquivo binario (5 numeros de posicoes aleatorias): " << endl;

    int i = 0;
    while(i < 5){
        Registro registro;
        int posRelativa = rand();
        int posAbusoluta = sizeof(Registro) * posRelativa;
        f_bin.seekg(posAbusoluta);
        f_bin.read((char*) &registro, sizeof(Registro));
        registro.depura(posRelativa);
        i++;
    }
}
