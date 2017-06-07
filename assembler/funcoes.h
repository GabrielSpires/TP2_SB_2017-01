#include <iostream> //IO (printf, scanf, etc)
#include <fstream> //IO de arquivos (fopen, etc)
#include <sstream> //Manipulação de strings
#include <iomanip> //Manipulaçao de IO (printar decimal como hexadecimal)
#include <vector> //TAD de lista
#include <bitset> //Variável do tipo binario

using namespace std;

typedef struct Tabela_tipos{
    string nome_operacao;
    int tipo_operacao;
}Tabela_tipos;

typedef struct Label{
    string nome_label;
    int endereco_label;
}Label;

int busca_tipo(string, vector<Tabela_tipos>);
int busca_label(string, vector<Label>);
string num_reg(string);
void traduz_programa_fonte(ifstream*, vector<bitset<8> >&, vector<Label>, vector<Tabela_tipos>, int);
void preenche_lista_labels(ifstream*, vector<Label>&, int*);
void escreve_cabecalho_mif(ofstream*);
void printa_memoria(ifstream*, ofstream*, vector<bitset<8> >, char const*);
void preenche_tabela_tipos(vector<Tabela_tipos>&);