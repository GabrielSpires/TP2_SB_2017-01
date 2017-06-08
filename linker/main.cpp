#include "funcoes_linker.h"

int main(int argc, char const *argv[]){
	ofstream saida;
	
	ligacao(&saida, argc, argv); //...

	saida.close();
	return 0;
}