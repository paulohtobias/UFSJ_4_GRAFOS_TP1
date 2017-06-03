#include "verificador.h"

int conta_valores_livres(int** sudoku, int tamanho){
	int i, j;
	int valores_livres = 0;
	for(i = 0; i < tamanho; i++){
		for (j = 0; j < tamanho; j++){
			if(sudoku[i][j] == 0){
				valores_livres++;
			}
		}
	}
	return valores_livres;
}

void cria_combinacao(int *vetor_combinacao, int tamanho){
	vetor_combinacao[tamanho-1]++;
	for(int i = tamanho-1; i >= 0 && vetor_combinacao[i]==10; i--){
		vetor_combinacao[i] = 1;
		vetor_combinacao[i-1]++;
	}
}

void inicializa_vetor(int* vetor, int tamanho, int valor){
	int i;
	for(i = 0; i < tamanho; i++){
		vetor[i] = valor;
	}
}

int* forca_bruta(int** sudoku, int tamanho, int altura, int largura){
	int i;
	int valores_livres = conta_valores_livres(sudoku, tamanho);
	int *vetor_de_combinacao = (int*) calloc(sizeof(int),valores_livres);
	inicializa_vetor(vetor_de_combinacao, valores_livres, 1);
	while(!testa_combinacao(vetor_de_combinacao,sudoku,tamanho,valores_livres)){
		cria_combinacao(vetor_de_combinacao,valores_livres);
	}
	for(i = 0; i < valores_livres; i++){
			printf("%d ",vetor_de_combinacao[i]);
		}printf("\n");
	return vetor_de_combinacao;
}

int** cria_matriz(int tamanho){
	int i;
	int **matriz = (int **)calloc(sizeof(int*),tamanho);
	for(i = 0; i < tamanho; i++){
		matriz[i] = (int*)calloc(sizeof(int),tamanho);
	}
	return matriz;
}

void insere_sudoku(int** sudoku,int tamanho){
	int vetor[] = {
		0,0,9,8,5,4,0,6,1,
		0,0,0,9,2,1,8,0,0,
		0,0,1,0,0,0,0,0,0,
		0,1,4,0,3,0,0,0,6,
		9,0,3,0,0,0,7,0,2,
		7,0,0,0,1,0,4,8,0,
		0,0,0,0,0,0,1,0,0,
		0,0,8,5,9,3,0,0,0,
		3,5,0,1,6,2,9,0,0};
	int k = 0;
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			sudoku[i][j] = vetor[k];
			k++;
		}
	}
}

int main(){
	int **sudoku = cria_matriz(9);
	insere_sudoku(sudoku,9);
	/*int vetor_combinacao[]={
		2,7,3,
		5,3,6,7,4,
		4,8,3,7,6,2,5,9,
		8,2,7,5,9,
		6,4,8,5,1,
		2,5,6,9,3,
		6,9,2,7,4,8,3,5,
		1,4,6,2,7,
		7,4,8};*/
	/*for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			printf("%d ",sudoku[i][j]);
		}printf("\n");
	}*/
	
	//printf("%d\n",testa_combinacao(vetor_combinacao,sudoku,9,conta_valores_livres(sudoku,9)));
	forca_bruta(sudoku,9,3,3);
	return 0;
}
