tp2: main.cpp funcoes_linker.cpp
	g++ -o link main.cpp funcoes_linker.cpp

run: main.cpp funcoes_linker.cpp
	@g++ -o link main.cpp funcoes_linker.cpp
	@reset
	./link programa ../tst/teste0/main.o ../tst/teste0/calc.o
	@# echo ""
	@# echo "*****************************"
	@# cat ligacao.temp
	@# @echo ""
	@# @echo "Arquivo: ligacao.temp"
	
fast: main.cpp funcoes_linker.cpp
	@g++ -o link main.cpp funcoes_linker.cpp
	@clear
	./link programa ../tst/teste1/main.o ../tst/teste1/op1_maior_3.o ../tst/teste1/op2_menor_3.o ../tst/teste1/op3_soma_3.o ../tst/teste1/op4_multiply_3.o ../tst/teste1/op5_media_3.o
	@#echo ""
	@#cat ligacao.temp
	@#echo ""
	@#echo "Arquivo: ligacao.temp"

clean: rm link 

	@# ./mont ../tst/teste1/main.a ../tst/teste1/main.o && ./mont ../tst/teste1/op1_maior_3.a ../tst/teste1/op1_maior_3.o && ./mont ../tst/teste1/op2_menor_3.a ../tst/teste1/op2_menor_3.o && ./mont ../tst/teste1/op3_soma_3.a ../tst/teste1/op3_soma_3.o && ./mont ../tst/teste1/op4_multiply_3.a ../tst/teste1/op4_multiply_3.o && ./mont ../tst/teste1/op5_media_3.a ../tst/teste1/op5_media_3.o