#include "verificador.h"

int piso(int valor1, int valor2){
	return (int)valor1/valor2;
}

int teto(int valor1, int valor2){
	int a = (int)valor1/valor2;
	if((float)valor1/valor2 > a){
		return a+1;
	}
	return a;
}

int verifica_horizontal(int **sudoku, int tamanho, int valor, int h){
	int i;
	for(i = 0; i < tamanho; i++){
		if(sudoku[h][i]==valor){
			return 0;
		}
	}
	return 1;
}

int verifica_vertical(int **sudoku, int tamanho, int valor, int v){
	int i;
	for(i = 0; i < tamanho; i++){
		if(sudoku[i][v]==valor){
			return 0;
		}
	}
	return 1;
}

int verifica_bloco(	int **sudoku, int valor, int horizontal, int vertical){
	int i, j;
	int quadrant_h = piso(horizontal,bloco_sudoku_h), //Quadrante horizontal
		quadrant_v = piso(vertical,bloco_sudoku_v); //Quadrante vertical

	for(i = quadrant_h*bloco_sudoku_h; ///Valor inicial
		i < quadrant_h*bloco_sudoku_h+bloco_sudoku_h; ///Condição
		i++){ ///Incremento
		for(j = quadrant_v*bloco_sudoku_v; ///Valor inicial
			j < quadrant_v*bloco_sudoku_v+bloco_sudoku_v; ///Condição
			j++){ ///Incremento
			if(sudoku[i][j]==valor){
				return 0;
			}
		}
	}
	return 1;
}

int verifica_valor_valido(int** sudoku, int tamanho, int valor, int h, int v){
	if(	verifica_horizontal(sudoku,tamanho,valor,h) &&
		verifica_vertical(sudoku,tamanho,valor,v) &&
		verifica_bloco(sudoku,valor,h,v)){
		return 1;
	}
	return 0;
}

int testa_combinacao(int* vetor_combinacao, int** sudoku,int tamanho, int qnt_livres){
	int i, j;
	int k = 0;
	for(i = 0; i < tamanho; i++){
		for( j = 0; j < tamanho; j++){
			if(sudoku[i][j]!=0){
				continue;
			}
			
			if(	verifica_valor_valido(sudoku,tamanho,vetor_combinacao[k],i,j) &&
				vetor_combinacao[k] != -1){
				k++;
			}else{
				return 0;
			}
		}
	}
	return 1;
}