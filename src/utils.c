#include "utils.h"

//Cria um vetor de tamanho d1 e o preenche com 0.
int *vetor1d(int d1){
    return (int*)calloc(d1, sizeof(int));
}

//Cria uma matriz d1 x d2 e a preenche com 0.
int **vetor2d(int d1, int d2){
    int **v2 = malloc(d1 * sizeof(int *));

    int i;
    for(i=0; i<d1; i++){
        v2[i] = vetor1d(d2);
    }

    return v2;
}
