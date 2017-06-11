#include "funcoes_linker.h"

int main(int argc, char const *argv[]){
    ofstream saida_montador; //Arquivo que vai ser gerado na função "ligacao()"
    ifstream saida_ligacao; //Vai ler o arquivo gerado na ligação pra ser usado depois
    vector<bitset<8> > memoria(256, 0); //Lista de 256 binarios de 8 bits iniciados com 0
    vector<Label> lista_labels; //Lista do tipo Label que guarda o nome e endereço de cada label
    vector<Extern> lista_externs;

    ligacao(&saida_montador, argc, argv);

    relocacao(&saida_ligacao, memoria, lista_labels, lista_externs);

    junta_labels(lista_labels);

    localiza_externs(lista_labels, lista_externs);

    recalcula_memoria(memoria, lista_labels);

    cout << " -------------------------- LABELS" << endl;
    for(int i=0; i<lista_labels.size(); i++){
        cout << lista_labels[i].nome_label << " "
             << lista_labels[i].endereco_label << " ";
        for(int j=0; j<lista_labels[i].endereco_instrucoes.size(); j++){
            cout << lista_labels[i].endereco_instrucoes[j] << " ";
        }cout << endl;
    }
    cout << " -------------------------- EXTERNS" << endl;
    for(int i=0; i<lista_externs.size(); i++){
        cout << lista_externs[i].nome_extern << " "
             << lista_externs[i].endereco_extern << " ";
        for(int j=0; j<lista_externs[i].endereco_instrucoes.size(); j++){
            cout << lista_externs[i].endereco_instrucoes[j] << " ";
        }cout << endl;
    }

    saida_ligacao.close();

    printa_memoria(memoria);
    
    return 0;
}

/*
    Operações que usam memória

    |op5|un3|addr8|
    jump    00111
    call    10011

    |op5|reg3|addr8|
    loadi   00001
    storei  00010
    jmpz    01000
    jmpn    01001
*/

// bitset<8> jooj = bitset<8>(string("00001010"));
// bitset<8> joooj = 1;
// bitset<8> jooooj = jooj.to_ulong()+joooj.to_ulong();

// cout << jooj.to_ulong() << endl;
// cout << joooj << endl;
// cout << jooooj << endl;

// cout << bitset<8>(jooj.to_ulong()+joooj.to_ulong()).to_string() << endl;