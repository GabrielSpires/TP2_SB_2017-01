#include "funcoes_linker.h"

void relocacao(ifstream* saida_ligacao, vector<bitset<8> > &memoria, vector<Label> &lista_labels){
	string linha, nome_modulo;
	stringstream linha_stream;
	int tamanho_modulo, constante_relocacao = 0;

	while(getline(*saida_ligacao, linha, '\n')){
		linha_stream.str(string("")); //Limpa a string pra ler a proxima
        linha_stream.clear(); //Apaga o buffer da string

		if(linha == "MODULE_START"){
			cout << "\ninicio de mod. detectado!" << endl;

			//Lê o nome do modulo
			getline(*saida_ligacao, linha, '\n');
			nome_modulo = linha;
			cout << "NOME: " + nome_modulo << endl;

			//Lê o tamanho do modulo
			getline(*saida_ligacao, linha, '\n');
			linha_stream << linha;
			linha_stream >> tamanho_modulo;
			constante_relocacao += tamanho_modulo;
			cout << "TAMANHO: " << tamanho_modulo << endl;
		}
		else if(linha == "##"){
			cout << "fim de lista de simbolos detectado!" << endl;
			cout << "CR: " << constante_relocacao << endl;

			//Lê o programa (binários) traduzidos pelo montador
			while(getline(*saida_ligacao, linha, '\n'), linha != "MODULE_END"){
				cout << linha << endl;
				if(linha == "00111" || linha == "10011" || linha == "00001" ||
				   linha == "00010" || linha == "01000" || linha == "01001"){
					
				}
			}
			/*
			    Operações que usam memória

			    |op5|un3|addr8|
			    jump    00111
			    call    10011

			    |op5|reg3|addr8|
			    loadi   00001
			    storei  00010
			    jmpz    01000
			    jmpn    01001
			*/
		}
		else if(linha == "MODULE_END"){
			cout << "fim de mod. detectado!" << endl;
		}
	}
}

//FAZER LISTA DE EXTERNS COM AS INTRUÇÕES EM ORDEM !!!!!!!!!!!!!!!!!!!!!!!! NO MONTADOR

// void preenche_lista_labels(ifstream* saida_ligacao, vector<Label> &lista_labels){
// 	stringstream instrucao;
//     string le_instrucao, label;
//     Label label_aux;

//     while(getline(*saida_ligacao, le_instrucao, '\n')){ //Lê a linha até o enter
//         instrucao.str(string("")); //Limpa a string pra ler a proxima
//         instrucao.clear(); //Apaga o buffer da string
//         instrucao << le_instrucao; //Joga o que foi lido na string manipulavel
//         instrucao >> label; //Lê a primeira informação da linha (operador ou label)

//         if (label[0] == '_'){ //Testa se é uma label (começa com "_")
//             label_aux.nome_label = label;
//         	instrucao >> label_aux.endereco_label;

//             lista_labels.push_back(label_aux);
//         }
//     }
//     //O arquivo foi todo lido, então precisamos resetar para ler denovo
//     saida_ligacao->clear(); //Limpa a flag EOS (End of File)
//     saida_ligacao->seekg(0, ios::beg); //Volta a ler do inicio do arquivo
// }

void ligacao(ofstream* entrada_ligacao, int argc, char const** argv){
	ifstream modulo_objeto;
	string linha_modulo;

	entrada_ligacao->open("ligacao.temp");

	for (int i = 2; i < argc; ++i){
		modulo_objeto.open(argv[i]);
		while(getline(modulo_objeto, linha_modulo, '\n')){
			*entrada_ligacao << linha_modulo << endl;
		}
		modulo_objeto.close();
	}
	entrada_ligacao->close();
}