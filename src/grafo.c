#include "grafo.h"

//Cria um novo grafo vazio com n vértices.
Grafo *novo_Grafo(int n){
    Grafo *grafo = malloc(sizeof(Grafo));

    grafo->n = n;
    grafo->m = 0;

    int i, j;
    grafo->adj = vetor2d(n, n);

    //Preenchendo o grafo com infinito em todas as arestas.
    for(i=0; i<n; i++){
        for(j=0; j<grafo->n; j++){
            grafo->adj[i][j] = INF;
        }
    }

    grafo->hiper_arestas = nova_Lista("hiper aresta");

    return grafo;
}
//Libera o grafo da memória.
void free_Grafo(Grafo *grafo){
    int i;
    for(i=0; i<grafo->n; i++){
        free(grafo->adj[i]);
    }
    free(grafo->adj);

    free(grafo);
}

//Insere uma aresta não-direcionada de u para v.
void grafo_insere_aresta_nd(Grafo *grafo, int u, int v, int peso){
    if((u < grafo->n) && (v < grafo->n)){
        grafo->adj[u][v] = peso;
    }
}
//Insere uma aresta direcionada entre u e v.
void grafo_insere_aresta_d(Grafo *grafo, int u, int v, int peso){
    grafo_insere_aresta_nd(grafo, u, v, peso);
    grafo_insere_aresta_nd(grafo, v, u, peso);
}

//Remove uma aresta não-direcionada de u para v.
void grafo_remove_aresta_nd(Grafo *grafo, int u, int v){
    if((u < grafo->n) && (v < grafo->n)){
        grafo->adj[u][v] = INF;
    }
}
//Remove uma aresta direcionada entre u e v.
void grafo_remove_aresta_d(Grafo *grafo, int u, int v){
    grafo_remove_aresta_nd(grafo, u, v);
    grafo_remove_aresta_nd(grafo, v, u);
}

//Verifica se existe aresta de u para v.
bool grafo_existe_aresta_nd(Grafo *grafo, int u, int v){
    if((u < grafo->n) && (v < grafo->n)){
        if(grafo->adj[u][v] != INF){
            return true;
        }
    }
    return false;
}
//Verifica se existe aresta entre u e v.
bool grafo_existe_aresta_d(Grafo *grafo, int u, int v){
    return ( (grafo_existe_aresta_nd(grafo, u, v)) &&
             (grafo_existe_aresta_nd(grafo, v, u)) );
}

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
