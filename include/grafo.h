#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "utils.h"

#ifndef INF
    #define INF 0x7fffffff
#endif //INF

typedef struct{
	int n;		            //Quantidade de vértices.
	int m;		            //Quantidade de arestas.
	int **adj; 	            //Matriz de adjacência.
	Lista *hiper_arestas;   //Lista de hiper-arestas.
}Grafo;

//Cria um novo grafo vazio com n vértices.
Grafo *novo_Grafo(int n);
//Libera o grafo da memória.
void free_Grafo(Grafo *grafo);

//Insere uma aresta não-direcionada de u para v.
void grafo_insere_aresta_nd(Grafo *grafo, int u, int v, int peso);
//Insere uma aresta direcionada entre u e v.
void grafo_insere_aresta_d(Grafo *grafo, int u, int v, int peso);

//Remove uma aresta não-direcionada de u para v.
void grafo_remove_aresta_nd(Grafo *grafo, int u, int v);
//Remove uma aresta direcionada entre u e v.
void grafo_remove_aresta_d(Grafo *grafo, int u, int v);

//Verifica se existe aresta de u para v.
int grafo_existe_aresta_nd(Grafo *grafo, int u, int v);
//Verifica se existe aresta entre u e v.
int grafo_existe_aresta_d(Grafo *grafo, int u, int v);

//Mostra o grafo na tela.
void grafo_mostra(Grafo *grafo);

#endif //GRAFO_H
