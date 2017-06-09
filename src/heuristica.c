#include "heuristica.h"

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
    int i, j;

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

    //printP(n, sudoku->dimensao);
    printS(sudoku);
    getchar();

    //variáveis responsáveis pela contagem de tempo de usuário e sistema.
	double tempoU,tempoS;
	struct rusage resources;
	struct timeval inicioU, inicioS, fimU, fimS;

    //Inicia a contagem de tempo do usuario e sistema.
    getrusage(RUSAGE_SELF, &resources);
    inicioU = resources.ru_utime;
    inicioS = resources.ru_stime;
    
    int coloriu;
    while(!sfim(sudoku->grafo)){
        coloriu = 0;
        
        //coloriu+= heuristica_vertice(sudoku);
        coloriu+= heuristica_hiper_aresta(sudoku);
        
        /*if(coloriu > 0){
            printP(n, sudoku->dimensao);
            printS(sudoku);
            getchar();
        }*/
    }
    // Finaliza a contagem de tempo do usuario e sistema.
    getrusage(RUSAGE_SELF, &resources);
    fimU = resources.ru_utime;
    fimS = resources.ru_stime;

    // Calcula o tempo do usuario.
    tempoU = (double) (fimU.tv_sec - inicioU.tv_sec) + 1.e-6 * (double) (fimU.tv_usec - inicioU.tv_usec);
    // Calcula o tempo do sistema.
    tempoS = (double) (fimS.tv_sec - inicioS.tv_sec) + 1.e-6 * (double) (fimS.tv_usec - inicioS.tv_usec);

    printf("Tempo de usuário: %.9f\n",tempoU);
	printf("Tempo de sistema: %.9f\n",tempoS);

    printS(sudoku);
}

int heuristica_vertice(Sudoku *sudoku){
    int i;
    int n = sudoku->grafo->n;

    int coloriu = 0;
    for(i=0; i<n; i++){
        if(possibilidades[i][0] == 1){
            int cor;
            for(cor=1; cor<=sudoku->dimensao; cor++){
                if(possibilidades[i][cor] == 1){
                    heuristica_pht_colore(sudoku->grafo, i, cor);
                    coloriu = 1;
                }
            }
        }
    }
    return coloriu;
}


int heuristica_hiper_aresta(Sudoku *sudoku){
    int c, i;
    No *temp;
    int n = sudoku->grafo->n;

    int coloriu = 0;

    for(c=1; c<=sudoku->dimensao; c++){
        for(temp = sudoku->grafo->hiper_arestas->primeiro; temp != NULL; temp = temp->proximo){
            int *hiper_aresta = temp->dado;
            
            int total = 0;
            int id = 0;
            for(i=0; i<n && total <= 1; i++){
                if(hiper_aresta[i] == 1 && sudoku->grafo->cor[i] == 0){
                    if(grafo_colore_vertice(sudoku->grafo, i, c) == true){
                        total+=possibilidades[i][c];
                        id = i;
                        grafo_colore_vertice(sudoku->grafo, i, 0);
                    }
                }
            }
            if(total == 1){
                heuristica_pht_colore(sudoku->grafo, id, c);
                coloriu = 1;

                //printP(n, sudoku->dimensao);
                //printS(sudoku);
                //getchar();
            }
        }
    }
    return coloriu;
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

int sfim(Grafo *g){
    int i, j;
    for(i=0; i<g->n; i++){
        if(g->cor[i] == 0){
            return 0;
        }
        for(j=i+1; j<g->n; j++){
            if(g->cor[j] == 0){
                return 0;
            }
            if(grafo_existe_aresta_nd(g, i, j)){
                if(g->cor[i] == g->cor[j]){
                    return 0;
                }
            }
        }
    }
    return 1;
}