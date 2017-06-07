#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cria um vetor de tamanho d1 e o preenche com 0.
int *vetor1d(int d1);

//Cria uma matriz d1 x d2 e a preenche com 0.
int **vetor2d(int d1, int d2);

//Sub vetor
int *sub_vetor(int *vetor, int inicio, int fim);

//Calcula a raiz de um quadrado perfeito.
int raiz_quadrado_perfeito(int quadrado_perfeito);

#endif // UTILS_H
