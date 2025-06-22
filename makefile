all: compila

compila: main.o fatoracaoLU.o
	gcc main.o fatoracaoLU.o -o prog

main.o: main.c
	gcc -c main.c

fatoracaoLU.o: fatoracaoLU.c
	gcc -c fatoracaoLU.c

del:
	rm main.o fatoracaoLU.o prog
