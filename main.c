#include "dsatur.h"
#include "backtracking.h"
#include "interface.h"

int main(int argc , char *argv[]){
	//gui(argc, argv); return 0;

	Sudoku *sudoku1 = novo_Sudoku(3, 3);
	sudoku_coloracao_string(sudoku1, "000000010400000000020000000000050407008000300001090000300400200050100000000806000");
	dsatur(sudoku1);
	printS(sudoku1);

	/**
	int i = 0, l = INF;
	FILE *in = fopen("testes/9.txt", "r");
	char coloracao[100];
	Sudoku *sudoku1 = novo_Sudoku(3, 3);
	while(i<l && !feof(in)){
		fscanf(in, "%s\n", coloracao);
		if(i<l){
			printf("%d: ", i);
			sudoku_coloracao_string(sudoku1, coloracao);
			algoritmo_exato(sudoku1);
			//gui(argc, argv, sudoku1);
		}
		i++;
	}
	return 0;
	/**/
}
