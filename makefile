all: compila

compila: main.o fatoracaoLU.o eliminacaoDeGauss.o
	gcc main.o fatoracaoLU.o eliminacaoDeGauss.o -o prog

main.o: main.c
	gcc -c main.c

fatoracaoLU.o: fatoracaoLU.c
	gcc -c fatoracaoLU.c

eliminacaoDeGauss.o:
	gcc -c eliminacaoDeGauss.c

rm:
	rm main.o fatoracaoLU.o prog

del:
	del main.o fatoracaoLU.o eliminacaoDeGauss.o prog
