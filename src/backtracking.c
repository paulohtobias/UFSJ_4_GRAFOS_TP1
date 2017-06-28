#include "backtracking.h"

//Matriz com as possibilidades de cores de cada vértice.
//Cada linha i corresponde ao id vértice i
//e cada coluna j (j > 0) corresponde à cor j.
//A posição [i][0] indica quantas cores o vértice i pode assumir.
int **possibilidades;

//Inicializa a mtriz de possibilidades.
void inicializa_possibilidades(Sudoku *sudoku){
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
        if(cor > 0){
			atualiza_possibilidades(sudoku, i, cor);
        }
    }
}

//Atualiza a matriz de possibilidades quando um vértice é colorido.
void atualiza_possibilidades(Sudoku *sudoku, int v, int cor){
	int i, j;
	//Zerando as possibilidades de cores de cor já que o vértice está colorido.
	for(i=0; i<=sudoku->dimensao; i++){
		possibilidades[v][i] = 0;
	}
	
	//Zerando as possibilidades de cores dos vértices adjacentes à i.
	for(i=0; i<sudoku->grafo->hiper_arestas_por_vertice; i++){
		int pos = sudoku->grafo->pos_hiper_aresta[v][i];
		for(j=0; j<sudoku->grafo->tam_hiper_arestas; j++){
			int u = sudoku->grafo->hiper_aresta[pos][j];
			if(u != v){
				int cor2 = sudoku->grafo->cor[u];
				if(cor2 == 0 && possibilidades[u][cor] == 1){
					possibilidades[u][cor] = 0;
					possibilidades[u][0]--;
				}
			}
		}
	}
}

//Tenta colorir um vértice. Se conseguir, então a matriz de
//possibilidades é atualizada.
void exato_colore(Grafo *grafo, int id, int cor){
	int dimensao = raiz_quadrado_perfeito(grafo->n);
    if(grafo_colore_vertice(grafo, id, cor) == true){
        int v;
		for(v=0; v<=dimensao; v++){
			possibilidades[id][v] = 0;
		}

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

//Função principal.
void algoritmo_exato(Sudoku *sudoku){
	inicializa_possibilidades(sudoku);
    
	/**
    printP(sudoku->grafo->n, sudoku->dimensao);
    printS(sudoku);
    getchar();
	/**/

    int coloriu = 0;
    while(!sfim(sudoku->grafo)){
        coloriu = 0;
        
        coloriu+= poda_vertice(sudoku);
		/**
        printP(sudoku->grafo->n, sudoku->dimensao);
        printS(sudoku);
        getchar();
		/**/
        
        coloriu+= poda_hiper_aresta(sudoku);
		/**
        printP(sudoku->grafo->n, sudoku->dimensao);
        printS(sudoku);
        getchar();
		/**/

        if(coloriu == 0){
            printf("BACKTRACKING: ");//getchar();

            coloriu = backtracking(sudoku);
            if(coloriu == 0){
                printf("Sem solução!\n");
                return;
            }
        }
    }

	//printf("Deu certo!\n");
}

//Funções de poda. Podem resolver o sudoku.
int poda_vertice(Sudoku *sudoku){
    int i;
    int n = sudoku->grafo->n;

    int coloriu = 0;
    for(i=0; i<n; i++){
        if(possibilidades[i][0] == 1){
            int cor;
            for(cor=1; cor<=sudoku->dimensao; cor++){
                if(possibilidades[i][cor] == 1){
                    exato_colore(sudoku->grafo, i, cor);
                    coloriu = 1;
                }
            }
        }
    }
    return coloriu;
}
int poda_hiper_aresta(Sudoku *sudoku){
    int c, i, j;
    int n = sudoku->grafo->n;
    int d = sudoku->dimensao;

    int coloriu = 0;
    int total = 0;

    for(c=1; c<=d; c++){
        int id;
        for(i=0; i<sudoku->grafo->qtd_hiper_arestas; i++){
            total = 0;
            id = 0;
            for(j=0; j<sudoku->grafo->tam_hiper_arestas && total <= 1; j++){
                int v = sudoku->grafo->hiper_aresta[i][j];
                int cor = sudoku->grafo->cor[v];
                if(possibilidades[v][c] == 1){
                    total++;
                    id = v;
                }
            }
            if(total == 1){
                exato_colore(sudoku->grafo, id, c);
                
                /**
                printP(sudoku->grafo->n, sudoku->dimensao);
                printS(sudoku);
                printf("Coloriu vertice %d com a cor %d\n", id, c);
                getchar();
                /**/
                
                coloriu = 1;
            }
        }
    }
    return coloriu;
}

//Funções de tentativa e erro.
void define_estaticos(int *vetor_combinacao, Grafo *grafo){
	int i;
	for( i = 0; i < grafo->n; i++){
		if(grafo->cor[i] > 0){
			vetor_combinacao[i] = estatico;
		}
	}
}
bool backtracking(Sudoku *sudoku){
	int k = 0;
    int menor_id_livre;
	int *vetor_combinacao = vetor1d(sudoku->grafo->n);
	define_estaticos(vetor_combinacao, sudoku->grafo);

    for(menor_id_livre=0; menor_id_livre<sudoku->grafo->n && vetor_combinacao[menor_id_livre] == estatico; menor_id_livre++){}

	while(vetor_combinacao[menor_id_livre] <= sudoku->dimensao && k < sudoku->grafo->n){
		if(vetor_combinacao[k] == estatico){
			k++;
		}else{
			vetor_combinacao[k]++;
			while(possibilidades[k][vetor_combinacao[k]] == 0){
				vetor_combinacao[k]++;
			}
			if(vetor_combinacao[menor_id_livre] > sudoku->dimensao){
				return false;
			}else if(vetor_combinacao[k] > sudoku->dimensao){
				vetor_combinacao[k] = 0;
				grafo_colore_vertice(sudoku->grafo, k, 0);
				k--;
				while(k>0 && vetor_combinacao[k] == estatico){
					k--;
				}
			}else if(grafo_colore_vertice(sudoku->grafo, k, vetor_combinacao[k])){
				k++;
			}
		}
	}
	return true;
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
