#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "sudoku.h"
#define estatico -1
typedef enum{
    NAO_COLORIU = 0,
    COLORIU = 1,
    FIM
}Exato_Estado;

//Inicializa a mtriz de possibilidades.
void inicializa_possibilidades(Sudoku *sudoku);

//Atualiza a matriz de possibilidades quando um vértice é colorido.
void atualiza_possibilidades(Sudoku *sudoku, int v, int cor);

//Tenta colorir um vértice. Se conseguir, então a matriz de
//possibilidades é atualizada.
void exato_colore(Sudoku *sudoku, int id, int cor);

//Função principal.
bool algoritmo_exato(Sudoku *sudoku);

//Funções de poda. Podem resolver o sudoku.
Exato_Estado poda_vertice(Sudoku *sudoku);
Exato_Estado poda_hiper_aresta(Sudoku *sudoku);

//Funções de tentativa e erro.
void define_estaticos(int *vetor_combinacao, Grafo *grafo);
bool backtracking(Sudoku *sudoku);

#endif //BACKTRACKING_H
