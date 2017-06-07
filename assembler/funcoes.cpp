#include "funcoes.h"

int busca_tipo(string campo, vector<Tabela_tipos> lista_tipos){
    for (int i = 0; i < lista_tipos.size(); i++){ //Passa  pela lista de tipos
        if (campo == lista_tipos[i].nome_operacao){ //Testa se o campo foi encontrado
            return lista_tipos[i].tipo_operacao; //Retorna o numero do tipo da instrução
        }
    }
    return -1; //Retorna -1 se nao encontrar nada (erro)
}

int busca_label(string nome_campo, vector<Label> lista_labels){

    for(int i=0; i<lista_labels.size(); i++){
        if(lista_labels[i].nome_label == nome_campo){
            return lista_labels[i].endereco_label;
        }
    }
    return -1;
}

string num_reg(string reg){
    string reg_num;

    if (reg == "A0"){
        reg_num = "000";
    }
    else if (reg == "A1"){
        reg_num = "001";
    }
    else if (reg == "A2"){
        reg_num = "010";
    }
    else if (reg == "A3"){
        reg_num = "011";
    }
    else if (reg == "A4"){
        reg_num = "100";
    }
    else if (reg == "A5"){
        reg_num = "101";
    }
    else if (reg == "A6"){
        reg_num = "110";
    }
    else if (reg == "A7"){
        reg_num = "111";
    }

    return reg_num;
}

void traduz_programa_fonte(ifstream *entrada, 
                            vector<bitset<8> > &memoria, 
                            vector<Label> lista_labels, 
                            vector<Tabela_tipos> lista_tipos,
                            int* ILC){
    stringstream instrucao; //String manipulável que guarda a instrução
    string le_instrucao, //Usada no getline() pra ler o arquivo
           campo, //Recebe um a um os campos da instrução
           operador, reg1, reg2, addr, un, sgn; //Operandos possiveis
    int pc = 0, addr_int, sgn_int, num_bytes, valor_data, tipo; //addr_int é a variável que converte o endereço de string p/ int
    string num_bytes_string, valor_data_string; //Variaveis usadas na pseudo instrução .data

    while(getline(*entrada, le_instrucao, '\n')){
        instrucao.str(string("")); //Limpa a string pra ler a proxima
        instrucao.clear(); //Apaga o buffer da string
        instrucao << le_instrucao; //Joga a string de le_instrucao na variavel instrucao
        instrucao >> campo; //Lê a primeira informação da instrucao (operador ou label)
        
        if(campo[0] == '_') instrucao >> campo; //Se leu uma label, leia o prox. campo
        if(campo[0] == '_'){ //Se ainda continua lendo a label é pq só tem a label na linha
            getline(*entrada, le_instrucao, '\n'); //Lê a próxima linha
            instrucao.str(string("")); //Limpa a string pra ler a proxima
            instrucao.clear(); //Apaga o buffer da string
            instrucao << le_instrucao; //Joga a string de le_instrucao na variavel instrucao
            instrucao >> campo; //Lê a primeira informação da instrucao (operador)
        }

        tipo = busca_tipo(campo, lista_tipos); //Busca na lista qual o tipo da instrução
        
        if (tipo == 1){ //exit, return |op|un| |5|11|
            if (campo == "exit"){
                memoria[pc] = bitset<8>(string("00000000")); //Escreve 8 zeros na memoria
                memoria[pc+1] = bitset<8>(string("00000000")); //Escreve 8 zeros na memoria
            }
            else if (campo == "return"){ //10100 |op|un| |5|11|
                operador = "10100";
                memoria[pc] = bitset<8>(string(operador + "000")); //Escreve o operando e completa com zeros
                memoria[pc+1] = bitset<8>(string("00000000")); //Escreve o segundo byte (8 zeros)
            }
        }
        else if (tipo == 2){ //loadi, storei, jmpz, jmpn |op|reg|addr| |5|3|8|
            if (campo == "loadi") operador = "00001"; //Binário do operador loadi
            else if (campo == "storei") operador = "00010";//Binário do operador storei
            else if (campo == "jmpz") operador = "01000"; //Binário do operador jmpz
            else if (campo == "jmpn") operador = "01001"; //Binário do operador jmp
            
            instrucao >> campo; //Lê o próximo campo
            reg1 = num_reg(campo); //Binário do registrador correspondente
            
            instrucao >> campo; //Lê o próximo campo
            if(campo[0] != '_'){ //Testa se o campo é um numero ou se é IO              
                if (campo == "IO"){ //Se o registrador for o de E/S entao a posição de mem. é a 254
                    addr = bitset<8>(254).to_string();
                }
                else { //Se for um numero é só converter pra inteiro e ler da memoria
                    istringstream(campo) >> addr_int; //Converte o end. lido em int
                    addr = bitset<8>(addr_int).to_string(); //Converte o inteiro em binario e o binario em string
                }
            }
            else{ //O campo é uma variavel que começa com "_"
                addr = bitset<8>(busca_label(campo, lista_labels)).to_string(); //Senão busca o end. da variavel
            }

            memoria[pc] = bitset<8>(operador+reg1); //Escreve o primeiro byte
            memoria[pc+1] = bitset<8>(addr); //Escreve o segundo byte
        }
        else if (tipo == 3){ //add, subtract, multiply, divide, move, load, store, negate |op|reg|reg|un| |5|3|3|5|
            if (campo == "add") operador = "00011";
            else if (campo == "subtract") operador = "00100";
            else if (campo == "multiply") operador = "00101";
            else if (campo == "divide") operador = "00110";
            else if (campo == "move") operador = "01010";
            else if (campo == "load") operador = "01011";
            else if (campo == "store") operador = "01100";
            else if (campo == "negate") operador = "01111";

            instrucao >> campo; //Lê o próximo campo
            reg1 = num_reg(campo); //Binário do registrador correspondente

            instrucao >> campo; //Lê o próximo campo
            reg2 = num_reg(campo); //Binário do registrador correspondente

            un = "00000"; //Bits que não são usados

            memoria[pc] = bitset<8>(operador+reg1); //Escreve o primeiro byte
            memoria[pc+1] = bitset<8>(reg2+un); //Escreve o segundo byte
        }
        else if (tipo == 4){ //jump, call |op|un|addr| |5|3|8|

            if (campo == "jump"){
                operador = "00111";

                instrucao >> campo; //Lê o próximo campo
                if(campo[0] != '_'){ //O campo lido não é uma label (é um inteiro)
                    istringstream(campo) >> addr_int; //Converte o end. lido em int
                    addr = bitset<8>(addr_int).to_string(); //Converte o inteiro em binario e o binario em string
                }
                else{ //O campo é uma label
                    addr = bitset<8>(busca_label(campo, lista_labels)).to_string(); //Senão busca o end. da variavel
                }
            }
            else if (campo == "call"){
                operador = "10011";

                instrucao >> campo;
                addr = bitset<8>(busca_label(campo, lista_labels)).to_string(); //Busca o end. da variavel
            }
            
            un = "000"; //Bits que não são usados

            memoria[pc] = bitset<8>(operador+un); //Escreve o primeiro byte
            memoria[pc+1] = bitset<8>(addr); //Escreve o segundo byte
        }
        else if (tipo == 5){ //loadc, addi |op|reg|sgn| |5|3|8|
            if (campo == "loadc") operador = "01101";
            else if (campo == "addi") operador = "10010";

            instrucao >> campo; //Lê o próximo campo
            reg1 = num_reg(campo); //Binário do registrador correspondente

            instrucao >> campo; //Lê o próximo campo (o immediato/constante)
            istringstream(campo) >> sgn_int; //Converte a constante lida em inteiro
            sgn = bitset<8>(sgn_int).to_string(); //Converte o inteiro em binário e depois em string

            memoria[pc] = bitset<8>(operador+reg1); //Escreve o primeiro byte
            memoria[pc+1] = bitset<8>(sgn); //Escreve o segundo byte            
        }
        else if (tipo == 6){ //clear, push, pop |op|reg|un| |5|3|8|
            if (campo == "clear") operador = "01110";
            else if (campo == "push") operador = "10000";
            else if (campo == "pop") operador = "10001";

            instrucao >> campo; //Lê o próximo campo
            reg1 = num_reg(campo); //Binário do registrador correspondente

            un = "00000000"; //Bits que não são usados

            memoria[pc] = bitset<8>(operador+reg1); //Escreve o primeiro byte
            memoria[pc+1] = bitset<8>(un); //Escreve o segundo byte
        }
        else if (tipo == 7){ // _label .data num_bytes valor
            instrucao >> campo; //Lê o numero de bytes a alocar
            istringstream(campo) >> num_bytes;

            instrucao >> campo; //Lê o valor a ser alocado
            istringstream(campo) >> valor_data; //Joga o valor (string) em um int

            valor_data_string = bitset<8*256>(valor_data).to_string(); //String de bits que guarda o valor

            //Guarda na memória cada byte do valor alocado, um a um
            //ILC é usado pra saber em qual posição a últma instrução foi colocada na memória
            for (int i = 0; i < num_bytes; i++, *ILC+=1){
                memoria[*ILC] = bitset<8>(valor_data_string.substr(valor_data_string.size()-(8*(num_bytes-i)), 8));
            }
        }
        pc += 2; //Incrementa o PC (cada instrução ocupa 2 espaços na mem.)
    }

    entrada->clear(); //Limpa a flag EOS (End of File)
    entrada->seekg(0, ios::beg); //Volta a ler do inicio do arquivo
}

void preenche_lista_labels(ifstream *entrada, vector<Label>& lista_labels, int *ILC){
    stringstream instrucao;
    string le_instrucao, label;
    Label label_aux;
    int pc = 0;

    while(getline(*entrada, le_instrucao, '\n')){ //Lê a linha até o enter
        instrucao.str(string("")); //Limpa a string pra ler a proxima
        instrucao.clear(); //Apaga o buffer da string
        instrucao << le_instrucao; //Joga o que foi lido na string manipulavel
        instrucao >> label; //Lê a primeira informação da linha (operador ou label)

        if (label[0] == '_'){ //Testa se é uma label (começa com "_")
            label_aux.nome_label = label;
            label_aux.nome_label.resize(label.size() -1); //Deleta o : da string (_sign: vira só _sign)
            label_aux.endereco_label = pc;

            lista_labels.push_back(label_aux);
            
            instrucao >> label;
            if(label == ".data") *ILC -= 2; //Se a instrução lida for .data não contar no ILC
            else if (label[0] == '_') pc -=2; //Se continua lendo label não contar essa posição
        }
        pc += 2;
    }
    //O arquivo foi todo lido, então precisamos resetar para ler denovo
    entrada->clear(); //Limpa a flag EOS (End of File)
    entrada->seekg(0, ios::beg); //Volta a ler do inicio do arquivo
    *ILC += pc;
}

void escreve_cabecalho_mif(ofstream *saida){
    *saida << "DEPTH = 256;\nWIDTH = 8;\nADDRESS_RADIX = HEX;\nDATA_RADIX = BIN;\nCONTENT\nBEGIN\n" << endl;
}

void printa_memoria(ifstream *entrada, ofstream *saida, vector<bitset<8> > memoria, char const* nome_entrada, int ILC, vector<Label> lista_labels){
    string le_instrucao, nome_modulo;
    int pc = 0;
    size_t diretorio;

    nome_modulo = nome_entrada;                     // Joga o argv[] numa string
    diretorio = nome_modulo.find_last_of("/");      // Acha na string onde começa o nome do arquivo
    nome_modulo = nome_modulo.substr(diretorio+1);  // Ignora o caminho do arquivo. Ex: "../tst/main.a" vira só "main.a"
    nome_modulo.resize(nome_modulo.size()-2);       // Retira a extensao do arquivo. Ex: "main.a" vira "main"

    *saida << nome_modulo << " = nome do modulo" << endl
           << ILC << " = tamanho do modulo" << endl;
    for(int i=0; i<lista_labels.size(); i++){
        *saida << lista_labels[i].nome_label << " " << lista_labels[i].endereco_label << endl;
    }
    *saida << "##" << endl;

    //Só printa no arquivo de acordo com o formato do modulo objeto
    for(int i=0; i<ILC/3/*memoria.size()*/; i++, pc++){ //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        *saida /*<< hex << setw(2) << setfill('0') << uppercase << pc << "        :  " */<< memoria[i] << endl;
        // if(i%2 == 0 && getline(*entrada, le_instrucao, '\n')){
        //  *saida << "              -- " << le_instrucao << endl;
        // }
        // else{
                // *saida << ";              -- " << endl;
        // }
    }
    // *saida << "END;" << endl; //Rodapé do arquivo de saída .mif
}

void preenche_tabela_tipos(vector<Tabela_tipos>& lista_tipos){
    /*  
        Preenche a tabela de tipos levando em consideração
        o número de registradores/operandos que cada instrução
        usa, ou seja, o formato de cada uma.
        Instruções com o mesmo formato são escritas da mesma
        forma na memória, com exceção do opcode, então é útil
        usar uma mesma função para escrever todas as funções de
        um mesmo tipo.
    */

    // |op5|un11|
    lista_tipos[0].nome_operacao = "exit";
    lista_tipos[0].tipo_operacao = 1;
    lista_tipos[1].nome_operacao = "return";
    lista_tipos[1].tipo_operacao = 1;

    // |op5|reg3|addr8|
    lista_tipos[2].nome_operacao = "loadi";
    lista_tipos[2].tipo_operacao = 2;
    lista_tipos[3].nome_operacao = "storei";
    lista_tipos[3].tipo_operacao = 2;
    lista_tipos[4].nome_operacao = "jmpz";
    lista_tipos[4].tipo_operacao = 2;
    lista_tipos[5].nome_operacao = "jmpn";
    lista_tipos[5].tipo_operacao = 2;

    // |op5|reg3|reg3|un5|
    lista_tipos[6].nome_operacao = "add";
    lista_tipos[6].tipo_operacao = 3;
    lista_tipos[7].nome_operacao = "subtract";
    lista_tipos[7].tipo_operacao = 3;
    lista_tipos[8].nome_operacao = "multiply";
    lista_tipos[8].tipo_operacao = 3;
    lista_tipos[9].nome_operacao = "divide";
    lista_tipos[9].tipo_operacao = 3;
    lista_tipos[10].nome_operacao = "move";
    lista_tipos[10].tipo_operacao = 3;
    lista_tipos[11].nome_operacao = "load";
    lista_tipos[11].tipo_operacao = 3;
    lista_tipos[12].nome_operacao = "store";
    lista_tipos[12].tipo_operacao = 3;
    lista_tipos[13].nome_operacao = "negate";
    lista_tipos[13].tipo_operacao = 3;

    // |op5|un3|addr8|
    lista_tipos[14].nome_operacao = "jump";
    lista_tipos[14].tipo_operacao = 4;
    lista_tipos[15].nome_operacao = "call";
    lista_tipos[15].tipo_operacao = 4;

    // |op5|reg3|sgn8|
    lista_tipos[16].nome_operacao = "loadc";
    lista_tipos[16].tipo_operacao = 5;
    lista_tipos[17].nome_operacao = "addi";
    lista_tipos[17].tipo_operacao = 5;

    // |op5|reg3|un8|
    lista_tipos[18].nome_operacao = "clear";
    lista_tipos[18].tipo_operacao = 6;
    lista_tipos[19].nome_operacao = "push";
    lista_tipos[19].tipo_operacao = 6;
    lista_tipos[20].nome_operacao = "pop";
    lista_tipos[20].tipo_operacao = 6;

    // |.data|numBytes|valor|
    lista_tipos[21].nome_operacao = ".data";
    lista_tipos[21].tipo_operacao = 7;
}