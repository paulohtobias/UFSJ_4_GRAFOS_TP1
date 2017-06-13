#include "sudoku.h"

//Cria um Sudoku vazio modelado como um grafo.
Sudoku *novo_Sudoku(int altura, int largura){
    Sudoku *sudoku = malloc(sizeof(Sudoku));

    int dimensao = altura * largura;
    int n = dimensao * dimensao;
    
    sudoku->grafo = novo_Grafo(n);

    sudoku->dimensao = dimensao;
    sudoku->altura = altura;
    sudoku->largura = largura;

    ///Criando as arestas.
    //Horizontal e Vertical
    int i, j;
    for(i=0; i<dimensao; i++){
        char *descricao_h = hiper_aresta_descricao("hiper aresta horizontal", i);
        lista_insere_final(sudoku->grafo->hiper_arestas, descricao_h, (void*)vetor1d(sudoku->grafo->n));
        int *hiper_aresta_horizontal = sudoku->grafo->hiper_arestas->ultimo->dado;

        char *descricao_v = hiper_aresta_descricao("hiper aresta vertical", i);
        lista_insere_final(sudoku->grafo->hiper_arestas, descricao_v, (void*)vetor1d(sudoku->grafo->n));
        int *hiper_aresta_vertical = sudoku->grafo->hiper_arestas->ultimo->dado;

        for(j=0; j<dimensao; j++){
            int idh = sudoku_lc_para_vertice_id(dimensao, i, j);
            hiper_aresta_horizontal[idh] = 1;

            int idv = sudoku_lc_para_vertice_id(dimensao, j, i);
            hiper_aresta_vertical[idv] = 1;
        }
        grafo_hiper_aresta_para_aresta(sudoku->grafo, hiper_aresta_horizontal);
        grafo_hiper_aresta_para_aresta(sudoku->grafo, hiper_aresta_vertical);
    }
    //Quadrantes
    sudoku_conecta_quadrantes(sudoku);

    return sudoku;
}


//Cria um Sudoku modelado como um grafo a partir de uma string.
Sudoku *novo_Sudoku_de_string(char *str_vertices, int altura, int largura){
    Sudoku *sudoku = novo_Sudoku(altura, largura);

    sudoku_coloracao_string(sudoku, str_vertices);

    return sudoku;
}

//Cria um Sudoku modelado como um grafo a partir de um arquivo.
Sudoku *novo_Sudoku_de_arquivo(char *arquivo){
    //Abrindo o arquivo.
    FILE *in = fopen(arquivo, "r");
    if(in == NULL){
        return NULL;
    }

    return NULL;
}

//Gera coloração inicial para um Sudoku a partir de uma string.
void sudoku_coloracao_string(Sudoku *sudoku, char *coloracao){
    int i;
    //Coloração inicial.
    for(i=0; i<sudoku->grafo->n; i++){
        sudoku->grafo->cor[i] = coloracao[i] - '0';
    }
}

//Converte uma posição do Sudoku para o id do vértice.
int sudoku_lc_para_vertice_id(int dimensao, int linha, int coluna){
    return (dimensao * linha) + coluna;
}

//Converte uma posição do Sudoku para a posição do grid.
int* sudoku_lc_para_quadrante_lc(int linha, int coluna, int largura, int altura){
    int *info = vetor1d(4);

    int quadrante_y = linha / altura;
    int quadrante_x = coluna / largura;

    int quadrante_linha = linha % altura;
    int quadrante_coluna = coluna % largura;

    info[0] = quadrante_y;
    info[1] = quadrante_x;

    info[2] = quadrante_linha;
    info[3] = quadrante_coluna;

    return info;
}

//Converte o id do vértice para uma posição do Sudoku.
//Retorno: vetor de int com dimensão 2. posição 0: linha
//                                      posição 1: coluna
int *vertice_id_para_sudoku_lc(int dimensao, int id){
    int *lc = vetor1d(2);

    lc[0] = id / dimensao;
    lc[1] = id % dimensao;

    return lc;
}

//Conecta um quadrante do Sudoku.
void sudoku_conecta_quadrantes(Sudoku *sudoku){
    int i, j, k;

    int largura = sudoku->largura;
    int altura = sudoku->altura;

    int id;

    int dimensao = raiz_quadrado_perfeito(sudoku->grafo->n);
    int quadrantes = sudoku->grafo->n / (largura * altura);
    int quadrantes_horizontal = dimensao / largura;

    for(k=0; k<quadrantes; k++){
        char *descricao = hiper_aresta_descricao("hiper aresta quadrante", k);
        lista_insere_final(sudoku->grafo->hiper_arestas, descricao, (void*)vetor1d(sudoku->grafo->n));
        int *hiper_aresta = sudoku->grafo->hiper_arestas->ultimo->dado;

        //printf("Quadrante %d\n", k);

        int i_inicio = (k / quadrantes_horizontal) * altura;
        int i_final = i_inicio + altura;

        for(i=i_inicio; i<i_final; i++){
            //printf("  linha %d\n", i);

            int j_inicio = (k % quadrantes_horizontal) * largura;
            int j_final = j_inicio + largura;
            for(j=j_inicio; j<j_final; j++){
                //printf("    coluna %d ## id: %d\n", j, sudoku_lc_para_vertice_id(dimensao, i, j));

                id = sudoku_lc_para_vertice_id(dimensao, i, j);
                hiper_aresta[id] = 1;
            }
        }
        /*for(i=0; i<grafo->n; i++){
            printf("%2d: %2d\n", i, hiper_aresta[i]);
        }*/
    }
    No *temp;
    for(temp = sudoku->grafo->hiper_arestas->primeiro; temp != NULL; temp = temp->proximo){
        grafo_hiper_aresta_para_aresta(sudoku->grafo, (int*)temp->dado);
    }
}

//Descrição de uma hiper-aresta do sudoku.
char *hiper_aresta_descricao(char *descricao, int numero){
    char *descricao_format = malloc(strlen(descricao) + 10);

    sprintf(descricao_format, "%s %d", descricao, numero);

    return descricao_format;
}

//Retorna o id dos vértices que pertecem ao quadrante.
int *sudoku_ids_quadrante(int altura, int largura, int x, int y){
    int *ids = vetor1d(altura * largura);

    int i, j, k = 0;
    int i_inicio = y * altura;
    int i_final = i_inicio + altura;
    int j_inicio = x * largura;
    int j_final = j_inicio + largura;
    for(i=i_inicio; i<i_final; i++){
        for(j=j_inicio; j<j_final; j++){
            ids[k++] = sudoku_lc_para_vertice_id(altura * largura, i, j);
        }
    }
    return ids;
}
