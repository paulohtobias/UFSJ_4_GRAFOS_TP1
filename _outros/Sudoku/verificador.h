#ifndef __VERIFICADORES
#define __VERIFICADORES

#include <stdio.h>
#include <stdlib.h>

#define bloco_sudoku_h 3
#define bloco_sudoku_v 3

int piso(int valor1, int valor2);
int teto(int valor1, int valor2);

int verifica_horizontal(int **sudoku, int tamanho, int valor, int h);
int verifica_vertical(int **sudoku, int tamanho, int valor, int v);
int verifica_bloco(	int **sudoku, int valor, int horizontal, int vertical);
int verifica_valor_valido(int** sudoku, int tamanho, int valor, int h, int v);

int testa_combinacao(int* vetor_combinacao, int** sudoku,int tamanho, int qnt_livres);
#endif