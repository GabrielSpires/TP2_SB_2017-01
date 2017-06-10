#include "funcoes_linker.h"

int main(int argc, char const *argv[]){
    ofstream entrada_ligacao; //Arquivo que vai ser gerado na função "ligacao()"
    ifstream saida_ligacao; //Vai ler o arquivo gerado na ligação pra ser usado depois
    vector<bitset<8> > memoria(256, 0); //Lista de 256 binarios de 8 bits iniciados com 0
    vector<Label> lista_labels; //Lista do tipo Label que guarda o nome e endereço de cada label

    ligacao(&entrada_ligacao, argc, argv);

    saida_ligacao.open("ligacao.temp");

    relocacao(&saida_ligacao, memoria, lista_labels);


    saida_ligacao.close();
    
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