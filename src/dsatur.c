#include "dsatur.c"

int vertice_maior_grau_saturacao(Grafo *grafo, int *cores){
	int i,j;
	int grau, saturacao;
	int maior;
	int grau_maior = 0, satur_maior = 0;
	int dimensao = grafo->n;

	for(i = 0, maior = 0; i < dimensao; i++){
		for(j = 0, grau = 0, saturacao = 0; j < dimensao; j++){
			if(grafo->adj[i][j] > 0){
				grau++;
				if(cores[j] > 0){
					saturacao++;
				}
			}
		}
		if(satur_maior < saturacao ){
			maior = i;
			grau_maior = grau;
			satur_maior = saturacao;
		}else if( satur_maior == saturacao && grau_maior < grau){
			maior = i;
			grau_maior = grau;
		}
	}

	return maior;
}

bool dsatur(Sudoku *sudoku){
	int cores = 0;
	int *vertices_cores = calloc(sizeof(int),grafo->n);
	printf("%d\n", vertice_maior_grau_saturacao(sudoku->grafo, vertices_cores));
}