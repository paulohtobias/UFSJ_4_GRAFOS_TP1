#include "heuristica_paulo.h"
#include "interface.h"

int main(int argc , char *argv[]){
	//gui(argc, argv); return 0;
	
	Sudoku *sudoku = novo_Sudoku("000000010400000000020000000000050407008000300001090000300400200050100000000806000",3,3);
	
	heuristica_pht(sudoku);
	
	return 0;
}
