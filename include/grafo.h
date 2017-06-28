#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "utils.h"

#ifndef INF
    #define INF 0x7fffffff
#endif //INF

//Definição e operações com Grafo.
typedef struct{
	int n;                          //Quantidade de vértices.
	int m;                          //Quantidade de arestas.
    
    int qtd_hiper_arestas;          //Quantidade de hiper-arestas.
    int tam_hiper_arestas;          //Tamanho das hiper-arestas.
    int hiper_arestas_por_vertice;  //Quantidade de hiper-arestas que cada vértice pertence.
    int **pos_hiper_aresta;         //Marca quais hiper-arestas o vértice pertence.
    int **hiper_aresta;             //Lista de hiper-arestas.
    
	int *cor;                       //Lista de cor de cada vertice.
}Grafo;

//Cria um novo grafo vazio com n vértices.
Grafo *novo_Grafo(int n, int qtd_hiper_arestas, int tam_hiper_arestas, int vertices_por_hiper_aresta);

//Libera o grafo da memória.
void free_Grafo(Grafo *grafo);

//Verifica se existe aresta de u para v.
int grafo_existe_aresta_nd(Grafo *grafo, int u, int v);

//Colore um vértice com a cor indicada.
//Retorna true (1) se foi possível colorir e false (0) se não.
bool grafo_colore_vertice(Grafo *grafo, int v, int cor);

//Exibe o grafo na tela.
void grafo_mostra(Grafo *grafo);

#endif //GRAFO_H
