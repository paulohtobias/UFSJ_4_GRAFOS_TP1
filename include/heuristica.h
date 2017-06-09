#ifndef HEURISTICA_H
#define HEURISTICA_H

#include "sudoku.h"
#include <sys/time.h>
#include <sys/resource.h>

/**
  * Dados necessários:
  *     - Sudoku (com grafo, altura, largura, etc)
  *     - matriz de possibilidades
  *     - heap (?)
  */

//Tenta colorir um vértice. Se conseguir, então a matriz de
//possibilidades é atualizada.
void heuristica_colore(Grafo *grafo, int id, int cor);

void heuristica_pht(Sudoku *sudoku);

int heuristica_vertice(Sudoku *sudoku);
int heuristica_hiper_aresta(Sudoku *sudoku);

void printP(int n, int d);

void printS(Sudoku *sudoku);

int sfim(Grafo *g);

#endif //HEURISTICA_H
