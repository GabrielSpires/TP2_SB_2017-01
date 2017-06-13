#include "funcoes_linker.h"

int main(int argc, char const *argv[]){
    ofstream saida_montador, saida_mif; //Arquivo que vai ser gerado na função "recebe_entrada()"
    ifstream saida_ligacao; //Vai ler o arquivo gerado na ligação pra ser usado depois
    vector<bitset<8> > memoria(256, 0); //Lista de 256 binarios de 8 bits iniciados com 0
    vector<Label> lista_labels; //Lista do tipo Label que guarda o nome e endereço de cada label
    vector<Extern> lista_externs;
    string nome_saida;

    //Cria o arquivo de saída do ligador com o formato .mif
    nome_saida = string(argv[1])+".mif";
    saida_mif.open(nome_saida.c_str());

    recebe_entrada(&saida_montador, argc, argv);

    ligacao(&saida_ligacao, memoria, lista_labels, lista_externs);

    junta_labels(lista_labels);

    localiza_externs(lista_labels, lista_externs);

    relocacao(memoria, lista_labels);
    
    printa_memoria(&saida_mif, memoria);
    
    saida_mif.close();
    return 0;
}