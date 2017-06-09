#include "funcoes_linker.h"

int main(int argc, char const *argv[]){
	ofstream saida_ligacao; //Arquivo que vai ser gerado na função "ligacao()"
	ifstream entrada_ligação; //Vai ler o arquivo gerado na ligação pra ser usado depois
	
	ligacao(&saida_ligacao, argc, argv);
	
	return 0;
}