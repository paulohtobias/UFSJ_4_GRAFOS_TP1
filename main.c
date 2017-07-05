#include <sys/time.h>
#include <sys/resource.h>
#include "dsatur.h"
#include "backtracking.h"
#include "interface.h"

int main(int argc , char *argv[]){
	//gui(argc, argv); return 0;

	/*Sudoku *sudoku1 = novo_Sudoku_de_arquivo("testes/casos/3x5_03.txt");
	return 0;*/

	/**
	Sudoku *sudoku2 = novo_Sudoku(3, 3);
	//sudoku_coloracao_string(sudoku2, "000000010400000000020000000000050407008000300001090000300400200050100000000806000");
    sudoku_coloracao_string(sudoku2, "000000010400000000020000000000050407008000300001090000300400200050100000000806000");
	algoritmo_exato(sudoku2);
    //dsatur(sudoku2);
	printS(sudoku2);
    return 0;
	/**/

	double tempoU,tempoS;
    struct rusage resources;
    struct timeval inicioU, inicioS, fimU, fimS;

    
	int i, inicio = 0, l = INF;
	FILE *in = fopen("testes/9.txt", "r");
	char coloracao[100];
	Sudoku *sudoku3 = novo_Sudoku(3, 3);
	for(i=inicio;0 && i<l && !feof(in); i++){
		fscanf(in, "%s\n", coloracao);
		sudoku_coloracao_string(sudoku3, coloracao);

		//Inicia a contagem de tempo do usuario e sistema.
		getrusage(RUSAGE_SELF, &resources);

		inicioU = resources.ru_utime;
		inicioS = resources.ru_stime;

		algoritmo_exato(sudoku3);

		getrusage(RUSAGE_SELF, &resources);

		fimU = resources.ru_utime;
		fimS = resources.ru_stime;

		// Calcula o tempo do usuario.
		tempoU = (double) (fimU.tv_sec - inicioU.tv_sec) + 1.e-6 * (double) (fimU.tv_usec - inicioU.tv_usec);
		// Calcula o tempo do sistema.
		tempoS = (double) (fimS.tv_sec - inicioS.tv_sec) + 1.e-6 * (double) (fimS.tv_usec - inicioS.tv_usec);

		printf("backtraking; 9; 0; ");
		printf("%.9f;",tempoU);
		printf("%.9f\n",tempoS);
	}
	fclose(in);

	in = fopen("testes/9.txt", "r");
	sudoku3 = novo_Sudoku(3, 3);
	for(i=inicio; i<l && !feof(in); i++){
		fscanf(in, "%s\n", coloracao);
		sudoku_coloracao_string(sudoku3, coloracao);

		//Inicia a contagem de tempo do usuario e sistema.
		printf("heuristica;");
		getrusage(RUSAGE_SELF, &resources);

		inicioU = resources.ru_utime;
		inicioS = resources.ru_stime;		

		dsatur(sudoku3);

		getrusage(RUSAGE_SELF, &resources);

		fimU = resources.ru_utime;
		fimS = resources.ru_stime;

		// Calcula o tempo do usuario.
		tempoU = (double) (fimU.tv_sec - inicioU.tv_sec) + 1.e-6 * (double) (fimU.tv_usec - inicioU.tv_usec);
		// Calcula o tempo do sistema.
		tempoS = (double) (fimS.tv_sec - inicioS.tv_sec) + 1.e-6 * (double) (fimS.tv_usec - inicioS.tv_usec);

		printf("%.9f;",tempoU);
		printf("%.9f\n",tempoS);
	}

	return 0;
	/**/
}
