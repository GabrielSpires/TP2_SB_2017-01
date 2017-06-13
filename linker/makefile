tp2: main.cpp funcoes_linker.cpp
	@g++ -o link main.cpp funcoes_linker.cpp

run: main.cpp funcoes_linker.cpp
	@g++ -o link main.cpp funcoes_linker.cpp
	@reset
	@./link ../calc ../tst/teste0/main.o ../tst/teste0/calc.o
	
teste1: main.cpp funcoes_linker.cpp
	@g++ -o link main.cpp funcoes_linker.cpp
	@clear
	@./link ../programa ../tst/teste1/main.o ../tst/teste1/op1_maior_3.o ../tst/teste1/op2_menor_3.o ../tst/teste1/op3_soma_3.o ../tst/teste1/op4_multiply_3.o ../tst/teste1/op5_media_3.o

clean: rm link