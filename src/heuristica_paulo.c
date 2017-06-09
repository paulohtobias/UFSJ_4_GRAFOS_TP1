#include "heuristica_paulo.h"

//Matriz com as possibilidades de cores de cada vértice.
//Cada linha i corresponde ao id vértice i
//e cada coluna j (j > 0) corresponde à cor j.
//A posição [i][0] indica quantas cores o vértice i pode assumir.
int **possibilidades;

void heuristica_pht_colore(Grafo *grafo, int id, int cor){
    if(grafo_colore_vertice(grafo, id, cor) == true){
        possibilidades[id][0] = 0;
        int v;
        for(v=0; v<grafo->n; v++){
            if(grafo->cor[v] == 0){
                if(grafo_existe_aresta_nd(grafo, id, v)){
                    if(possibilidades[v][cor] == 1){
                        possibilidades[v][cor] = 0;
                        possibilidades[v][0]--;
                    }
                }
            }
        }
    }
}

void heuristica_pht(Sudoku *sudoku){
    int i, j, k;

    int n = sudoku->grafo->n;
    //Iniciando a matriz.
    possibilidades = vetor2d(n, sudoku->dimensao + 1);
    for(i=0; i<n; i++){
        possibilidades[i][0] = sudoku->dimensao;
        for(j=1; j<=sudoku->dimensao; j++){
            //Inicialmente todas as cores são possíveis.
            possibilidades[i][j] = 1;
        }
    }

    for(i=0; i<n; i++){
        int cor = sudoku->grafo->cor[i];
        if(cor == 0){
            for(j=0; j<n; j++){
                if(grafo_existe_aresta_nd(sudoku->grafo, i, j)){
                    int cor2 = sudoku->grafo->cor[j];
                    if(cor2 > 0){
                        if(possibilidades[i][cor2] == 1){
                            possibilidades[i][cor2] = 0;
                            possibilidades[i][0]--;
                        }
                    }
                }
            }
        }else{
            for(j=0; j<=sudoku->dimensao; j++){
                possibilidades[i][j] = 0;
            }
        }
    }

    printP(n, sudoku->dimensao);
    printS(sudoku);
    getchar();
    
    while(1){
        for(i=0; i<n; i++){
            if(possibilidades[i][0] == 1){
                int cor;
                for(cor=1; cor<=sudoku->dimensao; cor++){
                    if(possibilidades[i][cor] == 1){
                        heuristica_pht_colore(sudoku->grafo, i, cor);
                        printP(n, sudoku->dimensao);
                        printS(sudoku);
                        getchar();
                    }
                }
            }
        }
    }
}

void printP(int n, int d){
    int i, j;
    for(i=0; i<n; i++){
        printf("%2d: ", i);
        for(j=0; j<=d; j++){
            printf("%d|", possibilidades[i][j]);
        }
        printf("\n");
    }
}

void printS(Sudoku *sudoku){
    int i, j;
    int d, l, a;
    d = sudoku->dimensao;
    l = sudoku->largura;
    a = sudoku->altura;

    for(i=0; i<d; i++){
        if(i%a == 0){
            printf("\n");
        }
        for(j=0; j<d; j++){
            int id = sudoku_lc_para_vertice_id(d, i, j);
            if(j%l == 0){
                printf("|");
            }
            printf("%3d ", sudoku->grafo->cor[id]);
        }
        printf("\n");
    }
}
