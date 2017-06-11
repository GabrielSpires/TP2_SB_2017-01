#include "funcoes.h"

int main(int argc, char const *argv[]){
    int ILC=0; //Instruction Location Counter (to usando pra saber até que posição a memória é usada)
    vector<bitset<8> > memoria(256, 0); //Lista de 256 binarios de 8 bits iniciados com 0
    vector<Label> lista_labels; //Lista do tipo Label que guarda o nome e endereço de cada label
    vector<Extern> lista_externs;
    vector<Label> lista_instrucoes;
    vector<Tabela_tipos> lista_tipos(23); //Lista que guarda os numeros dos tipos de operações suportadas
    ifstream entrada; //InputFile em assembly
    ofstream saida; //OutputFile em formato .mif

    entrada.open(argv[1]); //Abre o arquivo de entrada usando o primeiro argumento
    saida.open(argv[2]); //Cria o arquivo de saida

    //Escreve o cabeçalho do arquivo tipo .mif
    //escreve_cabecalho_mif(&saida);

    //Preenche a lista de tipos de instrução
    preenche_tabela_tipos(lista_tipos); 

    //Preenche a lista de externs com a lista de cada instrução que usa os externs
    preenche_lista_externs(&entrada, lista_externs);

    // for(int i=0; i<lista_externs.size(); i++){
    //     cout << lista_externs[i].nome_extern << " / " << lista_externs[i].endereco_extern << " / ";
    //     for(int j=0; j<lista_externs[i].endereco_instrucoes.size(); j++){
    //         cout << lista_externs[i].endereco_instrucoes[j] << " ";
    //     }
    //     cout << endl;
    // }

    //Preenche a lista de labels com o nome e endereço de cada uma
    preenche_lista_labels(&entrada, lista_labels, &ILC); //Passagem 1

    //Transforma cada instrução lida em seu equivalente binário
    traduz_programa_fonte(&entrada, memoria, lista_labels, lista_tipos, &ILC); //Passagem 2

    //Printa o conteúdo da memória no arquivo de saída
    printa_modulo(&entrada, &saida, memoria, argv[1], ILC, lista_labels, lista_externs);

    entrada.close();
    saida.close();
    return 0;
}

/*
    Montador
    
    0-Inicio do modulo
    1-Nome do modulo *
    2-Lista de EXTERNs *
    2/3-Lista de labels do modulo *
    4-Código *
    5-Dicionario de relocação*
    6-Final do módulo*
*/