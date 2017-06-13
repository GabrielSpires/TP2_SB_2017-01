tp1: main.cpp funcoes.cpp
	@g++ -o mont main.cpp funcoes.cpp

run: main.cpp funcoes.cpp
	@g++ -o mont main.cpp funcoes.cpp
	@reset
	./mont ../tst/teste1/main.a ../tst/teste1/main.o 
	./mont ../tst/teste1/op1_maior_3.a ../tst/teste1/op1_maior_3.o
	./mont ../tst/teste1/op2_menor_3.a ../tst/teste1/op2_menor_3.o
	./mont ../tst/teste1/op3_soma_3.a ../tst/teste1/op3_soma_3.o
	./mont ../tst/teste1/op4_multiply_3.a ../tst/teste1/op4_multiply_3.o
	./mont ../tst/teste1/op5_media_3.a ../tst/teste1/op5_media_3.o

val: main.cpp funcoes.cpp
	g++ -g -o mont main.cpp funcoes.cpp
	reset
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./mont ../tst/teste_moodle.a ../tst/teste_moodle.o

clean:
	rm mont