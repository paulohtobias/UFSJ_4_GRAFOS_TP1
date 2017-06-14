#ifndef DSATUR_H
#define DSATUR_H

#include "sudoku.h"

///Busca o vértice de maior grau e saturação
int vertice_maior_grau_saturacao(Grafo *grafo, int *cores);

///Heuristica de busca mínima de cores em um grafo
bool dsatur(Sudoku *sudoku);

#endif //DSATUR_H