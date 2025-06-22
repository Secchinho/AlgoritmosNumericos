all: compila

compila: main.o fatoracaoLU.o eliminacaoDeGauss.o gaussSeidel.o gaussJacobi.o
	gcc main.o fatoracaoLU.o eliminacaoDeGauss.o gaussSeidel.o gaussJacobi.o -o prog

main.o: main.c
	gcc -c main.c

fatoracaoLU.o: fatoracaoLU.c
	gcc -c fatoracaoLU.c

eliminacaoDeGauss.o: eliminacaoDeGauss.c
	gcc -c eliminacaoDeGauss.c

gaussSeidel.o: gaussSeidel.c
	gcc -c gaussSeidel.c

gaussJacobi.o: gaussJacobi.c
	gcc -c gaussJacobi.c

rm:
	rm main.o fatoracaoLU.o eliminacaoDeGauss.o gaussSeidel.o gaussJacobi.o prog

del:
	del main.o fatoracaoLU.o eliminacaoDeGauss.o gaussSeidel.o gaussJacobi.o prog
