#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "sudoku.h"
#define estatico -1

//Inicializa a mtriz de possibilidades.
void inicializa_possibilidades(Sudoku *sudoku);

//Tenta colorir um vértice. Se conseguir, então a matriz de
//possibilidades é atualizada.
void exato_colore(Grafo *grafo, int id, int cor);

//Função principal.
void algoritmo_exato(Sudoku *sudoku);

//Funções de poda. Podem resolver o sudoku.
int poda_vertice(Sudoku *sudoku);
int poda_hiper_aresta(Sudoku *sudoku);

//Funções de tentativa e erro.
void define_estaticos(int *vetor_combinacao, Grafo *grafo);
bool backtracking(Sudoku *sudoku);

int sfim(Grafo *g);
void printP(int n, int d);
void printS(Sudoku *sudoku);

#endif //BACKTRACKING_H
