#include "funcoes_linker.h"

void ligacao(ofstream* saida, int argc, const char* argv[]){
	ifstream modulo_objeto;
	string linha_modulo;

	saida->open(argv[1]);

	for (int i = 2; i < argc; ++i){
		modulo_objeto.open(argv[i]);
		while(getline(modulo_objeto, linha_modulo, '\n')){
			*saida << linha_modulo << endl;
		}
		modulo_objeto.close();
	}
}