#ifndef DSATUR_H
#define DSATUR_H

#include "sudoku.h"

///Define as cores estaticas do grafo e retorna o numero de posições restantes
int define_cores_iniciais(Grafo *grafo, int *vertices_cores);

///Busca o vértice de maior grau e saturação, e o retorna
int vertice_maior_grau_saturacao(Grafo *grafo);

///Heuristica de busca mínima de cores em um grafo
void dsatur(Sudoku *sudoku);

#endif //DSATUR_H