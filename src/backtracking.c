#include "backtracking.h"

//Matriz com as possibilidades de cores de cada vértice.
//Cada linha i corresponde ao id vértice i
//e cada coluna j (j > 0) corresponde à cor j.
//A posição [i][0] indica quantas cores o vértice i pode assumir.
int **possibilidades;

//Inicializa a matriz de possibilidades.
void inicializa_possibilidades(Sudoku *sudoku){
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
void exato_colore(Sudoku *sudoku, int id, int cor){
    if(grafo_colore_vertice(sudoku->grafo, id, cor) == true){
        atualiza_possibilidades(sudoku, id, cor);
    }
}

//Função principal.
bool algoritmo_exato(Sudoku *sudoku){
	inicializa_possibilidades(sudoku);

    while(true){
        Exato_Estado estado_vertice = poda_vertice(sudoku);
        if(estado_vertice == FIM){
            return true;
        }
        
        Exato_Estado estado_hiper = poda_hiper_aresta(sudoku);
        if(estado_hiper == FIM){
            return true;
        }

        if(estado_vertice == NAO_COLORIU && estado_hiper == NAO_COLORIU){
            return backtracking(sudoku);
        }
    }
}

//Funções de poda. Podem resolver o sudoku.
Exato_Estado poda_vertice(Sudoku *sudoku){
    int i;
    int n = sudoku->grafo->n;

    Exato_Estado estado = FIM;
    for(i=0; i<n; i++){
        if(possibilidades[i][0] > 0){
            if(estado == FIM){
                estado = NAO_COLORIU;
            }
        }
        if(possibilidades[i][0] == 1){
            int cor;
            for(cor=1; cor<=sudoku->dimensao; cor++){
                if(possibilidades[i][cor] == 1){
                    exato_colore(sudoku, i, cor);
                    estado = COLORIU;
                }
            }
        }
    }
    return estado;
}
Exato_Estado poda_hiper_aresta(Sudoku *sudoku){
    int c, i, j;
    int d = sudoku->dimensao;

    Exato_Estado estado = FIM;
    int total = 0;

    for(c=1; c<=d; c++){
        int id;
        for(i=0; i<sudoku->grafo->qtd_hiper_arestas; i++){
            total = 0;
            id = 0;
            for(j=0; j<sudoku->grafo->tam_hiper_arestas && total <= 1; j++){
                int v = sudoku->grafo->hiper_aresta[i][j];
                if(possibilidades[v][0] > 0){
                    if(estado == FIM){
                        estado = NAO_COLORIU;
                    }
                }
                if(possibilidades[v][c] == 1){
                    total++;
                    id = v;
                }
            }
            if(total == 1){
                exato_colore(sudoku, id, c);                
                estado = COLORIU;
            }
        }
    }
    return estado;
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
    if(menor_id_livre == sudoku->grafo->n){
        return true;
    }

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
