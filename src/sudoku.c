#include "sudoku.h"

//Cria um Sudoku vazio modelado como um grafo.
Sudoku *novo_Sudoku(int altura, int largura){
    Sudoku *sudoku = malloc(sizeof(Sudoku));

    int dimensao = altura * largura;
    int n = dimensao * dimensao;
    
    int qtd_hiper_arestas = dimensao * 3;
    
    
    sudoku->grafo = novo_Grafo(n, qtd_hiper_arestas, dimensao, 3);

    sudoku->dimensao = dimensao;
    sudoku->altura = altura;
    sudoku->largura = largura;

    ///Criando as arestas.
    //Horizontal e Vertical
    int i;
    int linha, coluna, quadrante = 0;
    for(i=0; i<n; i++){
        int *lc = vertice_id_para_sudoku_lc(dimensao, i);
        linha = lc[0];
        coluna = lc[1];
        quadrante = ((linha / altura) * dimensao / largura ) + (coluna / largura);
        
        //Hiper-Aresta Linha.
        sudoku->grafo->pos_hiper_aresta[i][0] = linha;
        sudoku->grafo->hiper_aresta[linha][coluna] = i;
        
        //Hiper-Aresta Coluna.
        int pos_coluna = coluna + dimensao;
        sudoku->grafo->pos_hiper_aresta[i][1] = pos_coluna;
        sudoku->grafo->hiper_aresta[pos_coluna][linha] = i;
        
        //Hiper-Aresta Quadrante.
        int pos_quadrante = quadrante + (dimensao * 2);
        sudoku->grafo->pos_hiper_aresta[i][2] = pos_quadrante;
        sudoku->grafo->hiper_aresta[pos_quadrante][ ( altura * (linha % altura)) + (coluna % largura) ] = i;
        
        free(lc);
        lc = NULL;
        
    }

    return sudoku;
}

//Cria um Sudoku modelado como um grafo a partir de uma string.
Sudoku *novo_Sudoku_de_string(const char *str_vertices, int altura, int largura){
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
    
    int altura, largura;
    fscanf(in, "%d %d\n", &altura, &largura);
    
    Sudoku *sudoku = novo_Sudoku(altura, largura);
    
    int i;
    for(i=0; i<sudoku->grafo->n; i++){
        int c;
        fscanf(in, "%d", &c);
        sudoku->grafo->cor[i] = c;
    }
    fclose(in);

    return sudoku;
}

//Libera o Sudoku da memória.
void free_Sudoku(Sudoku *sudoku){
    free_Grafo(sudoku->grafo);
    free(sudoku);
}

//Gera coloração inicial para um Sudoku a partir de uma string.
void sudoku_coloracao_string(Sudoku *sudoku, const char *coloracao){
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
