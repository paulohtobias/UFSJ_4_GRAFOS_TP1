#include "grafo.h"

//Cria um novo grafo vazio com n vértices.
Grafo *novo_Grafo(int n, int qtd_hiper_arestas, int tam_hiper_arestas, int hiper_aresta_por_vertice){
    Grafo *grafo = malloc(sizeof(Grafo));

    grafo->n = n;
    grafo->m = 0;
    grafo->qtd_hiper_arestas = qtd_hiper_arestas;
    grafo->tam_hiper_arestas = tam_hiper_arestas;
    grafo->hiper_arestas_por_vertice = hiper_aresta_por_vertice;
    
    grafo->pos_hiper_aresta = vetor2d(n, hiper_aresta_por_vertice);
    grafo->hiper_aresta = vetor2d(qtd_hiper_arestas, tam_hiper_arestas);
    grafo->cor = vetor1d(n);

    return grafo;
}

//Libera o grafo da memória.
void free_Grafo(Grafo *grafo){
    int i;
    for(i=0; i<grafo->n; i++){
        free(grafo->pos_hiper_aresta[i]);
    }
    free(grafo->pos_hiper_aresta);
    
    for(i=0; i<grafo->qtd_hiper_arestas; i++){
        free(grafo->hiper_aresta[i]);
    }
    free(grafo->hiper_aresta);
    
    free(grafo->cor);
    free(grafo);
}

//Verifica se existe aresta de u para v.
bool grafo_existe_aresta_nd(Grafo *grafo, int u, int v){
    int i, j;
    for(i=0; i<grafo->hiper_arestas_por_vertice; i++){
        int hiper_aresta = grafo->pos_hiper_aresta[u][i];
        for(j=0; j<grafo->tam_hiper_arestas; j++){
            if(grafo->hiper_aresta[hiper_aresta][j] == v){
                return true;
            }
        }
    }
    return false;
}

//Colore um vértice com a cor indicada.
//Retorna true (1) se foi possível colorir e false (0) se não.
bool grafo_colore_vertice(Grafo *grafo, int v, int cor){
    if(v < 0 || v >= grafo->n){
        return false;
    }

    if(grafo->cor[v] == cor){
        return true;
    }

    if(cor > 0){
        //Verifica se algum vértice adjacete à v já possui a mesma cor.
        int i, j;
        for(i=0; i<grafo->hiper_arestas_por_vertice; i++){
            //Número da hiper-aresta.
            int pos = grafo->pos_hiper_aresta[v][i];
            
            for(j=0; j<grafo->tam_hiper_arestas; j++){
                //Vértice adjacente à v.
                int u = grafo->hiper_aresta[pos][j];
                
                if(grafo->cor[u] == cor){
                    return false;
                }
            }
        }
    }

    grafo->cor[v] = cor;

    return true;
}

//Exibe o grafo na tela.
void grafo_mostra(Grafo *grafo){
    int i, j;
    
    for(i=0; i<grafo->n; i++){
        printf("%2d: %2d", i, grafo->pos_hiper_aresta[i][0]);
        for(j=1; j<grafo->hiper_arestas_por_vertice; j++){
            printf(", %2d", grafo->pos_hiper_aresta[i][j]);
        }
        printf("\n");
    }
    
    for(i=0; i<grafo->qtd_hiper_arestas; i++){
        printf("%2d: |", i);
        for(j=0; j<grafo->tam_hiper_arestas; j++){
            printf("%2d|", grafo->hiper_aresta[i][j]);
        }
        printf("\n");
    }
}