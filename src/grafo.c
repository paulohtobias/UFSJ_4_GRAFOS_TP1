#include "grafo.h"

//Cria um novo grafo vazio com n vértices.
Grafo *novo_Grafo(int n){
    Grafo *grafo = malloc(sizeof(Grafo));

    grafo->n = n;
    grafo->m = 0;

    int i;
    grafo->adj = malloc(n * sizeof(int*));
    for(i=0; i<n; i++){
        grafo->adj[i] = calloc(n, sizeof(int));
    }

    return grafo;
}
//Libera o grafo da memória.
void free_Grafo(Grafo *grafo);

//Insere uma aresta não-direcionada de u para v.
void grafo_insere_aresta_nd(Grafo *grafo, int u, int v);
//Insere uma aresta direcionada entre u e v.
void grafo_insere_aresta_d(Grafo *grafo, int u, int v);

//Remove uma aresta não-direcionada de u para v.
void grafo_remove_aresta_nd(Grafo *grafo, int u, int v);
//Remove uma aresta direcionada entre u e v.
void grafo_remove_aresta_d(Grafo *grafo, int u, int v);

//Verifica se existe aresta de u para v.
int grafo_existe_aresta_nd(Grafo *grafo, int u, int v);
//Verifica se existe aresta entre u e v.
int grafo_existe_aresta_d(Grafo *grafo, int u, int v);

//Mostra o grafo na tela.
void grafo_mostra(Grafo *grafo){
    int i, j;

	printf("|  id |");
	for(i=0; i<grafo->n; i++)
		printf("| %3d |", i);
	printf("\n");
	//Mostrando o conteudo do grafo.
	for(i=0; i<grafo->n; i++){
		printf("| %3d |", i);
		for(j=0; j<grafo->n; j++){
			if(grafo->adj[i][j] == INF)
				printf("| INF |");
            else if(grafo->adj[i][j] < INF)
				printf("|%5d|", grafo->adj[i][j]);
		}
		printf("\n");
	}
}
