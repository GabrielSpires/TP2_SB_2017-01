#include <iostream> //IO (printf, scanf, etc)
#include <fstream> //IO de arquivos (fopen, etc)
#include <sstream> //Manipulação de strings
#include <iomanip> //Manipulaçao de IO (printar decimal como hexadecimal)
#include <vector> //TAD de lista
#include <bitset> //Variável do tipo binario
using namespace std;


typedef struct Label{
    string nome_label;
    int endereco_label;
}Label;

/*
	Função que lê todos os módulos e
	junta eles em um arquivo só
*/
void ligacao(ofstream*, int, char const**);

void relocacao(ifstream*, vector<bitset<8> >&, vector<Label>&);