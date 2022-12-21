/*
 * project-implementation.cpp -> implementação do projeto pratico
 *
 * GAC108 - Estruturas de Dados
 * by Arthur Nunes, Caio Bastos e Pedro Rabelo - 2022
 * Utilizando IDE CLION
 *
 */

#include <iostream>
#include <cstring>
#include "CSVToBinary.h"
#include "registro.h"

using namespace std;

//metodo para realizar cadastro de um novo registro
Registro *cadastraRegistro() {
    Registro *registro = new Registro;
    string anz;
    string area;
    cout << "anzsic06:";
    cin >> anz;
    strcpy(registro->anzsic06, anz.c_str());
    cout << "Area:";
    cin >> area;
    strcpy(registro->Area, area.c_str());
    cout << "year:";
    cin >> registro->year;
    cout << "geo_count:";
    cin >> registro->geo_count;
    cout << "ec_count:";
    cin >> registro->ec_count;
    return registro;
}

/*
 * metodo que realiza  a inserção de elementos no arquivo
 * esse metodo vai subscrever o registro que esta alocado na posição absoluta
 * Não conseguimos realizar a inserção sem subscrever o registro
 */
void adicionarElemento(int pos, Registro *&novoRg, fstream& arquivo){
    int posAbsoluta = sizeof(Registro) * pos;
    arquivo.seekg(posAbsoluta);
    arquivo.write((char *) novoRg, sizeof(Registro));
}

void buscarRegistro(int pos, fstream& arquivo);

/*
 * metodo que gerencia a inserção do elemento no arquivo e depois imprime a partir do arquivo.bin
 */
void insereElemento(fstream& arquivo) {
    Registro *novoRegistro = cadastraRegistro();
    int pos;
    cout << "posicao especifica qualquer:";
    cin >> pos;
    adicionarElemento(pos, novoRegistro, arquivo);
    buscarRegistro(pos, arquivo);
    delete novoRegistro;
}

//metodo para listar registros a partir do arquivo em um determinado
void listarRegistros(int inicio, int fim, fstream& arquivo){
    while (inicio <= fim){
        if(inicio >= 0){
            int posAbsoluta = sizeof(Registro) * inicio;
            Registro *registro = new Registro;
            arquivo.seekg(posAbsoluta);
            arquivo.read((char*) registro, sizeof(Registro));
            registro->depura(inicio);
            delete registro;
        }
        inicio++;
    }
}

//metodo para visualizar registros de x até y
//com tratativa de erro para leitura de elemento fora do alcance do arquivo
void visualizarRegistros(fstream& arquivo, int quantidadeMaximaElementos){
    int x, y;
    cout << "x:";
    cin >> x;
    while(x > quantidadeMaximaElementos) {
        cout << "posicao x maior que a quantidade de elementos" << endl;
        cout << "x:";
        cin >> x;
    }
    cout << "y:";
    cin >> y;
    while(y <= x) {
        cout << "posicao y menor que x" << endl;
        cout << "y:";
        cin >> y;
    }
    listarRegistros(x, y, arquivo);
}

//metodo para editar um registro no arquivo
//o metodo vai subscrever o atual elemento na posição absoluta
Registro *editarRegistro(Registro *&registro, int pos){
    cout << "Registro atual:";
    registro->depura(pos);
    Registro *novoRegistro = cadastraRegistro();
    return novoRegistro;
}

//metodo para gerenciar a edição de registro no arquivo binario
void alteraDadosRegistro(fstream& arquivo){
    Registro *registro = new Registro;
    int pos;
    cout << "posicao especifica qualquer:";
    cin >> pos;
    int posAbsoluta = sizeof(Registro) * pos;

    //faz a listagem do registro atual com uma posição anterior e posterior
    listarRegistros(pos - 1 , pos + 1, arquivo);

    //pegar o registro atual
    arquivo.seekg(posAbsoluta);
    arquivo.read((char*) registro, sizeof(Registro));

    //cria o registro para editar
    Registro *registroEditado = editarRegistro(registro, pos);

    //subscreve o registro atual
    arquivo.seekg(posAbsoluta);
    arquivo.write((char*) registroEditado, sizeof(Registro));

    cout << "Registro editado:";
    registroEditado->depura(pos);

    //faz a listagem depois de editado
    listarRegistros(pos - 1, pos + 1, arquivo);
}

//metodo para trocar posições de registros
void trocarRegistros(fstream& arquivo, CSVToBinary &csvToBinary){
    Registro *primeiroRegistro = new Registro;
    Registro *segundoRegistro = new Registro;
    int pos1, pos2;

    cout << "primeira posicao especifica qualquer:";
    cin >> pos1;
    cout << "segunda posicao especifica qualquer:";
    cin >> pos2;

    cout << endl;

    cout << "Listagem Antes: (posicao anterior e posterior)" << endl;
    cout << "Primeiro registro: " << endl;
    listarRegistros(pos1 - 1, pos1 + 1, arquivo);

    cout << endl;

    cout << "Segundo registro: " << endl;
    listarRegistros(pos2 - 1, pos2 + 1, arquivo);

    cout << endl;

    int posAbsoluta1 = sizeof(Registro) * pos1;
    arquivo.seekg(posAbsoluta1);
    arquivo.read((char*) primeiroRegistro, sizeof(Registro));

    int posAbsoluta2 = sizeof(Registro) * pos2;
    arquivo.seekg(posAbsoluta2);
    arquivo.read((char*) segundoRegistro, sizeof(Registro));

    arquivo.seekg(posAbsoluta1);
    arquivo.write((char*) segundoRegistro, sizeof(Registro));

    arquivo.seekg(posAbsoluta2);
    arquivo.write((char*) primeiroRegistro, sizeof(Registro));

    arquivo.close();
    arquivo.open(csvToBinary.arq_bin);

    cout << "Listagem Depois:" << endl;
    cout << "Primeiro registro: " << endl;
    listarRegistros(pos2 - 1, pos2 + 1, arquivo);

    cout << endl;

    cout << "Segundo registro: " << endl;
    listarRegistros(pos1 - 1, pos1 + 1, arquivo);
}

//imprime todos registros do aqruivo binario
void imprimeTodosRegistros(fstream& arquivo, CSVToBinary &csvToBinary){
    Registro *registro = new Registro;
    unsigned i = 0;
    cout << csvToBinary.quantidadeDados << endl;
    while (arquivo.read((char *) registro, sizeof(Registro))){
        registro->depura(i);
        i++;
    }
}

//busca um registro especifico a partir da posição absoluta
void buscarRegistro(int pos, fstream& arquivo){
    Registro *registro = new Registro;
    int posAbsoluta = sizeof(Registro) * pos;
    arquivo.seekg(posAbsoluta);
    arquivo.read((char*) registro, sizeof(Registro));
    registro->depura(pos);
}

//gerencia a busca de um dado no arquivo binario
void buscarDado(fstream& arquivo){
    int pos;
    cout << "posicao especifica qualquer:";
    cin >> pos;
    buscarRegistro(pos, arquivo);
}

//metodo para aceeso de funções no console
void selecionaOpcoes(int arg, CSVToBinary &csvToBinary) {
    fstream arquivo(csvToBinary.arq_bin, ios::binary | ios::out | ios::in);
    switch (arg) {
        case 1: {
            insereElemento(arquivo);
            break;
        }
        case 2: {
            visualizarRegistros(arquivo, csvToBinary.quantidadeDados);
            break;
        }
        case 3: {
            alteraDadosRegistro(arquivo);
            break;
        }
        case 4: {
            trocarRegistros(arquivo, csvToBinary);
            break;
        }
        case 5: {
            imprimeTodosRegistros(arquivo, csvToBinary);
            break;
        }
        case 6: {
            buscarDado(arquivo);
            break;
        }
        case 7: {
            csvToBinary.testeArquivoBinario();
            break;
        }
        case 8: {
            cout << "Quantidade dados arquivo: " << csvToBinary.quantidadeDados << " registros" << endl;
            break;
        }
        case 9: {
            cout << "Saindo...";
            break;
        }
        default:
            cout << "Operacao Invalida!" << endl;
            break;
    }
    arquivo.close();
}

//metodo para visualizar as opções no console
void mostraOpcoes() {
    cout << "OPCOES: " << endl;
    cout << "[1] - Adicionar um elemento no arquivo binario em uma posicao especifica qualquer." << endl;
    cout << "[2] - Visualizar os registros entre a posicao x e y." << endl;
    cout << "[3] - Alterar os dados de um registro em uma posicao especifica." << endl;
    cout << "[4] - Trocar dois registros de posicao no arquivo" << endl;
    cout << "[5] - Imprimir todos os registros do arquivo binario" << endl;
    cout << "[6] - Buscar registro especifico a partir da posicao." << endl;
    cout << "[7] - Testar Arquivo Binario." << endl;
    cout << "[8] - Visualizar quantidade de dados no arquivo binario" << endl;
    cout << "[9] - Sair." << endl;
    cout << "Escolha uma opcao:";
}

int main() {
    string arquivoBinario = "Data7602DescendingYearOrder.bin";
    string arquivoCSV = "Data7602DescendingYearOrder.csv";
    CSVToBinary csvToBinary(arquivoCSV, arquivoBinario);

    int opcao;

    do {
        mostraOpcoes();

        cin >> opcao;

        selecionaOpcoes(opcao, csvToBinary);

    } while (opcao != 9);

    return 0;
}
