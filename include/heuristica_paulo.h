#ifndef HEURISTICA_PAULO_H
#define HEURISTICA_PAULO_H

#include "sudoku.h"

/**
  * Dados necessários:
  *     - Sudoku (com grafo, altura, largura, etc)
  *     - matriz de possibilidades
  *     - heap (?)
  */

/**
  * Mudança de planos:
  * é preciso armazenar onde as cores se encaixam, e não quais vértices podem ter quais cores.
  * tem que ver onde o 5 pode ir, aí checa se duas cores entram em conflito.
  */

//Tenta colorir um vértice. Se conseguir, então a matriz de
//possibilidades é atualizada.
void heuristica_pht_colore(Grafo *grafo, int id, int cor);

void heuristica_pht(Sudoku *sudoku);

void printP(int n, int d);

void printS(Sudoku *sudoku);

#endif //HEURISTICA_PAULO_H
