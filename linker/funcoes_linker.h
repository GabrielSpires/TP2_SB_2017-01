#include <iostream> //IO (printf, scanf, etc)
#include <fstream> //IO de arquivos (fopen, etc)
#include <sstream> //Manipulação de strings
#include <iomanip> //Manipulaçao de IO (printar decimal como hexadecimal)
#include <vector> //TAD de lista
#include <bitset> //Variável do tipo binario
#include <cstdlib>
using namespace std;


typedef struct Label{
    string nome_label;
    int endereco_label;
    vector<int> endereco_instrucoes;
}Label;

typedef struct Extern{
	string nome_extern;
	int endereco_extern;
	vector<int> endereco_instrucoes;
}Extern;


// Função que lê todos os módulos e
// junta eles em um arquivo só
void ligacao(ofstream*, int, char const**);

// Função que recalcula os endereços
// de memória usados no programa
void relocacao(ifstream*, vector<bitset<8> >&, vector<Label>&);

void limpa_string(stringstream&);