#ifndef SUDOKU_H
#define SUDOKU_H

#include "grafo.h"

typedef struct{
    Grafo *grafo;
    int dimensao;
    int altura;
    int largura;
}Sudoku;

//Cria um Sudoku vazio modelado como um grafo.
Sudoku *novo_Sudoku(int altura, int largura);

//Cria um Sudoku modelado como um grafo a partir de uma string.
Sudoku *novo_Sudoku_de_string(const char *str_vertices, int altura, int largura);

//Cria um Sudoku modelado como um grafo a partir de um arquivo.
Sudoku *novo_Sudoku_de_arquivo(char *arquivo);

//Libera o Sudoku da memória.
void free_Sudoku(Sudoku *sudoku);

//Gera coloração inicial para um Sudoku a partir de uma string.
void sudoku_coloracao_string(Sudoku *sudoku, const char *coloracao);

//Converte uma posição do Sudoku para o id do vértice.
int sudoku_lc_para_vertice_id(int dimensao, int linha, int coluna);

//Converte uma posição do Sudoku para a posição do grid.
int* sudoku_lc_para_quadrante_lc(int linha, int coluna, int largura, int altura);

//Converte o id do vértice para uma posição do Sudoku.
//Retorno: vetor de int com dimensão 2. posição 0: linha
//                                      posição 1: coluna
int *vertice_id_para_sudoku_lc(int dimensao, int id);

//Conecta um quadrante do Sudoku.
void sudoku_conecta_quadrantes(Sudoku *grafo);

//Descrição de uma hiper-aresta do sudoku.
char *hiper_aresta_descricao(char *format, int numero);

//Retorna o id dos vértices que pertecem ao quadrante.
int *sudoku_ids_quadrante(int altura, int largura, int x, int y);

#endif // SUDOKU_H
