tp2: main.cpp funcoes_linker.cpp
	g++ -o link main.cpp funcoes_linker.cpp

run: main.cpp funcoes_linker.cpp
	@g++ -o link main.cpp funcoes_linker.cpp
	./link programa.mif ../tst/teste0/main.o ../tst/teste0/calc.o
	@cat programa.mif

clean: rm link