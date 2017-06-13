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
void recebe_entrada(ofstream*, int, char const**);

//Lê as informações dadas pelo montador como a lista de
//labels, lista de externs e constantes contidas no código
void ligacao(ifstream*, vector<bitset<8> >&, vector<Label>&, vector<Extern>&);

//Junta as labels com o mesmo nome
//pra ter todos os endereços num
//índice so da lista
void junta_labels(vector<Label>&);

//Procura as externs na lista de labels pra descobrir
    //o endereço onde cada extern foi declarado
void localiza_externs(vector<Label>&, vector<Extern>&);

//Recalcula os endereços de memória no código
void relocacao(vector<bitset<8> >&, vector<Label>);

//Limpa a string usada para ler os arquivos
void limpa_string(stringstream&);

//Printa o binário seguindo o padrão
//dos arquivos .mif
void printa_memoria(ofstream *, vector<bitset<8> >);