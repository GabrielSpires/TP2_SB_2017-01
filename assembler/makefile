tp1: main.cpp funcoes.cpp
	g++ -o mont main.cpp funcoes.cpp
	@echo ""
	@echo "Programa compilado com sucesso!"
	@echo "Um executável chamado 'mont' foi criado."
	@echo "Para executar use o comando ./mont entrada.a saida.o"
	@echo ""
	@echo "Para testar uma das saídas use o comando 'make run'"
	@echo "Para remover o executável compilado use o comando 'make clean'"
	@echo ""

run: main.cpp funcoes.cpp
	@g++ -o mont main.cpp funcoes.cpp
	@reset
	@./mont ../tst/teste_moodle.a ../tst/teste_moodle.o
	@echo ""
	@echo "Abrindo arquivo '../tst/teste_moodle.o'..."
	@echo ""
	@cat ../tst/teste_moodle.o

val: main.cpp funcoes.cpp
	g++ -g -o mont main.cpp funcoes.cpp
	reset
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./mont ../tst/teste_moodle.a ../tst/teste_moodle.o

clean:
	rm mont