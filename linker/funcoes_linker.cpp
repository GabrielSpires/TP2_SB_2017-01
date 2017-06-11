#include "funcoes_linker.h"

void limpa_string(stringstream& linha_stream){
	linha_stream.str(string("")); //Limpa a string pra ler a proxima
    linha_stream.clear(); //Apaga o buffer da string
}

void relocacao(ifstream* saida_ligacao, vector<bitset<8> > &memoria, vector<Label> &lista_labels){
	string linha, nome_modulo, campo;
	stringstream linha_stream;
	Label label_aux;
	int tamanho_modulo, constante_relocacao = 0, endereco;

	saida_ligacao->open("ligacao.temp");

	while(getline(*saida_ligacao, linha, '\n')){
		limpa_string(linha_stream);

		if(linha == "MODULE_START"){
			cout << "\ninicio de mod. detectado!" << endl;

			getline(*saida_ligacao, linha, '\n');
			linha_stream << linha;
			
			//Lê o NOME do modulo
			linha_stream >> nome_modulo;
			cout << "NOME: " + nome_modulo << endl;

			//Lê o TAMANHO do modulo
			linha_stream >> tamanho_modulo;
			constante_relocacao += tamanho_modulo;
			cout << "TAMANHO: " << tamanho_modulo << endl;

			//Lê as LABELS
			while(getline(*saida_ligacao, linha, '\n'), linha != "END_LABELS"){
				limpa_string(linha_stream);
				linha_stream << linha;

				linha_stream >> label_aux.nome_label;	  //Lê e salva o nome da label

				linha_stream >> label_aux.endereco_label; //Lê e salva o endereço onde a label foi declarada

				//Salva numa lista cada endereço em que a label foi usada
				while(linha_stream >> campo, campo != "X"){
					endereco = atoi(campo.c_str());
					label_aux.endereco_instrucoes.push_back(endereco);
				}

				//Adiciona a label na lista
				lista_labels.push_back(label_aux);

				//Limpa a lista de endereços do aux
				label_aux.endereco_instrucoes.clear();
			}
		}
		else if(linha == "##"){
			cout << "fim de lista de simbolos detectado!" << endl;
			cout << "CR: " << constante_relocacao << endl;

			//Lê o programa (binários) traduzidos pelo montador
			while(getline(*saida_ligacao, linha, '\n'), linha != "MODULE_END"){
				
			}
		}
		else if(linha == "MODULE_END"){
			cout << "fim de mod. detectado!" << endl;
		}
	}
	saida_ligacao->close();
}

void ligacao(ofstream* saida_montador, int argc, char const** argv){
	ifstream modulo_objeto;
	string linha_modulo;

	saida_montador->open("ligacao.temp");

	for (int i = 2; i < argc; ++i){
		modulo_objeto.open(argv[i]);
		while(getline(modulo_objeto, linha_modulo, '\n')){
			*saida_montador << linha_modulo << endl;
		}
		modulo_objeto.close();
	}
	saida_montador->close();
}