#include "funcoes.h"

int main(int argc, char const *argv[]){
    int ILC=0; //Instruction Location Counter (to usando pra saber até que posição a memória é usada)
    vector<bitset<8> > memoria(256, 0); //Lista de 256 binarios de 8 bits iniciados com 0
    vector<Label> lista_labels; //Lista do tipo Label que guarda o nome e endereço de cada label
    vector<Tabela_tipos> lista_tipos(22); //Lista que guarda os numeros dos tipos de operações suportadas
    ifstream entrada; //InputFile em assembly
    ofstream saida; //OutputFile em formato .mif

    entrada.open(argv[1]); //Abre o arquivo de entrada usando o primeiro argumento
    saida.open(argv[2]); //Cria o arquivo de saida

    //Escreve o cabeçalho do arquivo tipo .mif
    // escreve_cabecalho_mif(&saida);

    //Preenche a lista de tipos de instrução
    preenche_tabela_tipos(lista_tipos); 

    //Preenche a lista de labels com o nome e endereço de cada uma
    preenche_lista_labels(&entrada, lista_labels, &ILC); //Passagem 1

    //Transforma cada instrução lida em seu equivalente binário
    traduz_programa_fonte(&entrada, memoria, lista_labels, lista_tipos, ILC); //Passagem 2

    //Printa o conteúdo da memória no arquivo de saída
    printa_memoria(&entrada, &saida, memoria);

    entrada.close();
    saida.close();
    return 0;
}