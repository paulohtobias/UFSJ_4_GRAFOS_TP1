#ifndef SUDOKU_H
#define SUDOKU_H

#include "grafo.h"

//Cria um grafo modelado como um tabuleiro de Sudoku.
Grafo *novo_Sudoku(char *str_vertices, int largura, int altura);

//Converte uma posi��o do Sudoku para o id do v�rtice.
int sudoku_lc_para_vertice_id(int dimensao, int linha, int coluna);

//Converte uma posi��o do Sudoku para a posição do grid
int* sudoku_lc_para_quadrante_lc(int linha, int coluna, int largura, int altura);

//Converte o id do v�rtice para uma posi��o do Sudoku.
//Retorno: vetor de int com dimens�o 2. posi��o 0: linha
//                                      posi��o 1: coluna
int *vertice_id_para_sudoku_lc(int dimensao, int id);

//Conecta um quadrante do Sudoku.
void sudoku_conecta_quadrantes(Grafo *grafo, int largura, int altura);

//Descri��o de uma hiper-aresta do sudoku.
char *hiper_aresta_descricao(char *format, int numero);

//Retorna o id dos vértices que pertecem ao quadrante.
int *sudoku_ids_quadrante(int altura, int largura, int x, int y);

#endif // SUDOKU_H
