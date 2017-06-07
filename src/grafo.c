#include "grafo.h"

//Cria um novo grafo vazio com n vértices.
Grafo *novo_Grafo(int n){
    Grafo *grafo = malloc(sizeof(Grafo));

    grafo->n = n;
    grafo->m = 0;

    grafo->adj = vetor2d(n, n);

    //Preenchendo o grafo com infinito em todas as arestas.

    grafo->cor = vetor1d(n);

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
void grafo_insere_aresta_nd(Grafo *grafo, int u, int v){
    grafo_insere_aresta_d(grafo, u, v);
    grafo_insere_aresta_d(grafo, v, u);
}
//Insere uma aresta direcionada entre u e v.
void grafo_insere_aresta_d(Grafo *grafo, int u, int v){
    if((u >= 0 && u < grafo->n) && (v >= 0 && v < grafo->n)){
        grafo->adj[u][v] = 1;
    }
}

//Converte uma hiper-aresta para arestas do grafo.
void grafo_hiper_aresta_para_aresta(Grafo *grafo, int *hiper_aresta){
    int i, j;

    for(i=0; i<grafo->n-1; i++){
        if(hiper_aresta[i] == 1){
            for(j=i+1; j<grafo->n; j++){
                if(hiper_aresta[j] == 1){
                    grafo_insere_aresta_nd(grafo, i, j);
                }
            }
        }
    }
}

//Remove uma aresta não-direcionada de u para v.
void grafo_remove_aresta_nd(Grafo *grafo, int u, int v){
    grafo_remove_aresta_nd(grafo, u, v);
    grafo_remove_aresta_nd(grafo, v, u);
}
//Remove uma aresta direcionada entre u e v.
void grafo_remove_aresta_d(Grafo *grafo, int u, int v){
    if((u >= 0 && u < grafo->n) && (v >= 0 && v < grafo->n)){
        grafo->adj[u][v] = 0;
    }
}

//Verifica se existe aresta de u para v.
bool grafo_existe_aresta_nd(Grafo *grafo, int u, int v){
    return ( (grafo_existe_aresta_d(grafo, u, v)) && (grafo_existe_aresta_d(grafo, v, u)) );
}
//Verifica se existe aresta entre u e v.
bool grafo_existe_aresta_d(Grafo *grafo, int u, int v){
    if((u >= 0 && u < grafo->n) && (v >= 0 && v < grafo->n)){
        if(grafo->adj[u][v] != 0){
            return true;
        }
    }
    return false;
}

//Colore um vértice com a cor indicada.
//Retorna true (1) se foi possível colorir e false (0) se não.
bool grafo_colore_vertice(Grafo *grafo, int v, int cor){
    if(v < 0 || v >= grafo->n){
        return false;
    }

    int u;

    //Verifica se algum vértice adjacete à v já possui a mesma cor.
    for(u=0; u<grafo->n; u++){
        if(grafo_existe_aresta_nd(grafo, v, u) && grafo->cor[u] == cor){
            return false;
        }
    }

    grafo->cor[v] = cor;

    return true;
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
