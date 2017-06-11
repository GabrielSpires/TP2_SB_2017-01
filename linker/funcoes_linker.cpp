#include "funcoes_linker.h"

void limpa_string(stringstream& linha_stream){
	linha_stream.str(string("")); //Limpa a string pra ler a proxima
    linha_stream.clear(); //Apaga o buffer da string
}

void relocacao(ifstream* saida_ligacao, vector<bitset<8> > &memoria, vector<Label> &lista_labels, vector<Extern>& lista_externs){
	string linha, nome_modulo, campo;
	stringstream linha_stream;
	Label label_aux;
	Extern extern_aux;
	int tamanho_modulo = 0, constante_relocacao = 0, endereco, pc = 0;

	saida_ligacao->open("ligacao.temp");

	while(getline(*saida_ligacao, linha, '\n')){
		limpa_string(linha_stream);

		if(linha == "MODULE_START"){
			// cout << "\ninicio de mod. detectado!" << endl;
			constante_relocacao += tamanho_modulo;

			getline(*saida_ligacao, linha, '\n');
			linha_stream << linha;
			
			//Lê o NOME do modulo
			linha_stream >> nome_modulo;
			// cout << "NOME: " + nome_modulo << endl;

			//Lê o TAMANHO do modulo
			linha_stream >> tamanho_modulo;
			// cout << "TAMANHO: " << tamanho_modulo << endl;
			// cout << "CONST RELOC: " << constante_relocacao << endl;
			//Lê as LABELS
			while(getline(*saida_ligacao, linha, '\n'), linha != "END_LABELS"){
				limpa_string(linha_stream);
				linha_stream << linha;

				linha_stream >> label_aux.nome_label;	  //Lê e salva o nome da label

				linha_stream >> label_aux.endereco_label; //Lê e salva o endereço onde a label foi declarada
				if(label_aux.nome_label != "const") label_aux.endereco_label += constante_relocacao;

				//Salva numa lista cada endereço em que a label foi usada
				while(linha_stream >> campo, campo != "X"){
					endereco = atoi(campo.c_str());
					label_aux.endereco_instrucoes.push_back(endereco+constante_relocacao);
				}

				//Adiciona a label na lista
				lista_labels.push_back(label_aux);

				//Limpa a lista de endereços do aux
				label_aux.endereco_instrucoes.clear();
			}
			//Lê as externs
			while(getline(*saida_ligacao, linha, '\n'), linha != "END_EXTERNS"){
				limpa_string(linha_stream);
				linha_stream << linha;

				linha_stream >> extern_aux.nome_extern;	  //Lê e salva o nome da extern

				linha_stream >> extern_aux.endereco_extern; //Lê e salva o endereço onde a extern foi declarada (flag)

				//Salva numa lista cada endereço em que a extern foi usada
				while(linha_stream >> campo, campo != "X"){
					endereco = atoi(campo.c_str());
					extern_aux.endereco_instrucoes.push_back(endereco+constante_relocacao);
				}

				//Adiciona a extern na lista
				lista_externs.push_back(extern_aux);

				//Limpa a lista de endereços do aux
				extern_aux.endereco_instrucoes.clear();
			}
			while(getline(*saida_ligacao, linha, '\n'), linha != "MODULE_END"){
				memoria[pc] = bitset<8>(linha);
				pc++;
			}
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

void printa_memoria(ofstream *saida_mif, vector<bitset<8> > memoria){
    string le_instrucao;
    int pc = 0;

    *saida_mif << "DEPTH = 256;\nWIDTH = 8;\nADDRESS_RADIX = HEX;\nDATA_RADIX = BIN;\nCONTENT\nBEGIN\n" << endl;

    //Só printa no arquivo de acordo com o formato do arquivo .mif
    for(int i=0; i<memoria.size(); i++, pc++){
        *saida_mif << hex << setw(2) << setfill('0') << uppercase << pc << "        :  " << memoria[i] << ";";
        *saida_mif << "              -- " << endl;
    }
    *saida_mif << "END;" << endl; //Rodapé do arquivo de saída .mif
}

void junta_labels(vector<Label> &lista_labels){
	for(int i=0; i<lista_labels.size(); i++){
		for(int j=i+1; j<lista_labels.size(); j++){
			if(lista_labels[i].nome_label == lista_labels[j].nome_label){
				
				for(int k=0; k<lista_labels[j].endereco_instrucoes.size(); k++){
					lista_labels[i].endereco_instrucoes.push_back(lista_labels[j].endereco_instrucoes[k]);
				}
				lista_labels.erase(lista_labels.begin()+j);
			}
		}
	}
}

void localiza_externs(vector<Label>& lista_labels, vector<Extern>& lista_externs){
	for(int i=0; i<lista_externs.size(); i++){ 								//Pra cada extern
		for(int j=0; j<lista_labels.size(); j++){ 							//Procurar na lista de labels
			if(lista_externs[i].nome_extern == lista_labels[j].nome_label){ //Uma label igual ao extern
				
				for(int k=0; k<lista_externs[i].endereco_instrucoes.size(); k++){
					lista_labels[j].endereco_instrucoes.push_back(lista_externs[i].endereco_instrucoes[k]);
				}
				lista_externs.erase(lista_externs.begin()+i);
			}
		}
	}
}

void recalcula_memoria(vector<bitset<8> >& memoria, vector<Label> lista_labels){
	for(int i=0; i<lista_labels.size(); i++){
		if(lista_labels[i].nome_label != "const"){
			
			for(int j=0; j<lista_labels[i].endereco_instrucoes.size(); j++){
				memoria[lista_labels[i].endereco_instrucoes[j] + 1] = lista_labels[i].endereco_label;
			}

		}
	}
}