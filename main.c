#include <sys/time.h>
#include <sys/resource.h>
#include "dsatur.h"
#include "backtracking.h"
#include "interface.h"

int main(int argc , char *argv[]){
	//gui(argc, argv); return 0;

	/*Sudoku *sudoku = novo_Sudoku_de_arquivo("testes/casos/3x5_03.txt");
	return 0;*/

	/*
	Sudoku *sudoku1 = novo_Sudoku(3, 3);
	sudoku_coloracao_string(sudoku1, "000000010400000000020000000000050407008000300001090000300400200050100000000806000");
	dsatur(sudoku1);
	printS(sudoku1);
    return 0;
	/**/

	/**/

	double tempoU,tempoS;
    struct rusage resources;
    struct timeval inicioU, inicioS, fimU, fimS;

    //Inicia a contagem de tempo do usuario e sistema.
    getrusage(RUSAGE_SELF, &resources);

    inicioU = resources.ru_utime;
    inicioS = resources.ru_stime;

	int i = 0, l = 24575;
	FILE *in = fopen("testes/9.txt", "r");
	char coloracao[100];
	Sudoku *sudoku1 = novo_Sudoku(3, 3);
	while(i<l && !feof(in)){
		fscanf(in, "%s\n", coloracao);
		if(i<l){
			sudoku_coloracao_string(sudoku1, coloracao);
			algoritmo_exato(sudoku1);
		}
		i++;
	}

	getrusage(RUSAGE_SELF, &resources);

    fimU = resources.ru_utime;
    fimS = resources.ru_stime;

	printf("backtraking; %d\n");

	//Inicia a contagem de tempo do usuario e sistema.
    getrusage(RUSAGE_SELF, &resources);

    inicioU = resources.ru_utime;
    inicioS = resources.ru_stime;

	int i = 0, l = 24575;
	FILE *in = fopen("testes/9.txt", "r");
	char coloracao[100];
	Sudoku *sudoku1 = novo_Sudoku(3, 3);
	while(i<l && !feof(in)){
		fscanf(in, "%s\n", coloracao);
		if(i<l){
			sudoku_coloracao_string(sudoku1, coloracao);
			dsatur(sudoku1);
		}
		i++;
	}

	getrusage(RUSAGE_SELF, &resources);

    fimU = resources.ru_utime;
    fimS = resources.ru_stime;

	printf("heuristica; %d\n");

	return 0;
	/**/
}
