#include "backtracking.h"
#include "interface.h"

int main(int argc , char *argv[]){
	
	//Sudoku *sudoku = novo_Sudoku_de_string("000000010400000000020000000000050407008000300001090000300400200050100000000806000",3,3);
	//heuristica_pht(sudoku);

	//gui(argc, argv, sudoku); return 0;
	
	/**
	heuristica_pht(sudoku);
	return 0;
	/**/

	/**/
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
