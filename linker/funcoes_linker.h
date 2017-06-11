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
void relocacao(ifstream*, vector<bitset<8> >&, vector<Label>&, vector<Extern>&);

//Junta as labels com o mesmo nome
//pra ter todos os endereços num
//índice so da lista
void junta_labels(vector<Label>&);

void localiza_externs(vector<Label>&, vector<Extern>&);

void recalcula_memoria(vector<bitset<8> >&, vector<Label>);

void limpa_string(stringstream&);

void printa_memoria(/*ofstream *, */vector<bitset<8> >);