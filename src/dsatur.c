#include "dsatur.h"
#define sem_cor 0

int vertice_maior_grau_saturacao(Grafo *grafo){
	int i,j,k;
	int grau, saturacao;
	int maior; //Vertice com maior saturação e grau
	int grau_maior = 0, satur_maior = 0;
	int n = grafo->n;

	///Percorre cada vértice
    for(i=0, maior = 0; i<n; i++){
        if(grafo->cor[i] == 0){
            grau = 0;
            saturacao = 0;
            for(j=0; j<grafo->hiper_arestas_por_vertice; j++){
                int pos = grafo->pos_hiper_aresta[i][j];
                for(k=0; k<grafo->tam_hiper_arestas; k++){
                    grau++;
                    int i2 = grafo->hiper_aresta[pos][k];
                    if(grafo->cor[i2] > 0){
                        saturacao++;
                    }
                }
            }
            
            ///Se o vértice possuir maior saturação
            if(satur_maior < saturacao ){
                maior = i;
                grau_maior = grau;
                satur_maior = saturacao;

            ///Se possuir maior grau e saturação igual ao maior mais antigo
            }else if( satur_maior == saturacao && grau_maior < grau){
                maior = i;
                grau_maior = grau;
            }
        }
    }
    /*
	for(i = 0, maior = 0; i < n; i++){
        if(grafo->cor[i] == sem_cor){
            grau = 0;
            saturacao = 0;
            ///Percorre seus vizinhos
            for(j = 0; j < n; j++){
                ///Se for o vértice não foi colorido
                if( grafo_existe_aresta_nd(grafo, i, j)){
                    grau++; //Aumenta o grau do vertice
                    if(grafo->cor[j] > 0){
                        saturacao++; //Aumenta a saturação do vértice
                    }
                }
            }

            ///Se o vértice possuir maior saturação
            if(satur_maior < saturacao ){
                maior = i;
                grau_maior = grau;
                satur_maior = saturacao;

            ///Se possuir maior grau e saturação igual ao maior mais antigo
            }else if( satur_maior == saturacao && grau_maior < grau){
                maior = i;
                grau_maior = grau;
            }
        }
	}
    */

	return maior;
}

///Define as cores estaticas do grafo e retorna o numero de posições restantes
int define_cores_iniciais(Grafo *grafo, int *vertices_cores){
	int i;
	int posicoes_restantes = 0;
	for(i = 0; i < grafo->n; i++){
		if(grafo->cor[i] == sem_cor){
			posicoes_restantes++;
		}else{
			vertices_cores[grafo->cor[i]-1] = 1;
		}
	}
	return posicoes_restantes;
}

void dsatur(Sudoku *sudoku){
	int i;
	int quantidade_passou = 0;
	int n = sudoku->grafo->n;

	int *vertices_cores = vetor1d(n); ///Vetor que armazena as cores já usadas
	int posicoes_restantes = define_cores_iniciais(sudoku->grafo, vertices_cores);
	while(posicoes_restantes > 0){
		///Pega o vértice de maior grau e saturação
		int vertice = vertice_maior_grau_saturacao(sudoku->grafo);
		///Percorre todas as cores disponíveis no momento
		for(i = 1; i <= n; i++){
			///Se for possível colorí-lo com alguma das cores
			if(vertices_cores[i-1] != sem_cor && grafo_colore_vertice(sudoku->grafo, vertice, i)){
				if(i > sudoku->dimensao){
					quantidade_passou++;
				}
				posicoes_restantes--;
				break;
			}
		}
		
		///Se não conseguiu colorir
		if(sudoku->grafo->cor[vertice] == sem_cor){
			///Procura uma cor não usada ainda a define no vértice
			for(i = 1; i <= n; i++){
				if(vertices_cores[i-1] == sem_cor){
					vertices_cores[i-1]=1;
					posicoes_restantes--;
					grafo_colore_vertice(sudoku->grafo,vertice,i);
					break;
				}
			}
		}
	}
	for(i=sudoku->dimensao; vertices_cores[i] > 0; i++){}
	printf("%d;%d;",i,quantidade_passou);
}