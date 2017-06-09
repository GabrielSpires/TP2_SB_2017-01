#include "funcoes_linker.h"

void ligacao(ofstream* saida_ligacao, int argc, char const** argv){
	ifstream modulo_objeto;
	string linha_modulo;

	saida_ligacao->open("ligacao.temp");

	for (int i = 2; i < argc; ++i){
		modulo_objeto.open(argv[i]);
		while(getline(modulo_objeto, linha_modulo, '\n')){
			*saida_ligacao << linha_modulo << endl;
		}
		modulo_objeto.close();
	}
	saida_ligacao->close();
}