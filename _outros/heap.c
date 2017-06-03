#include <stdio.h>
#include <stdlib.h>

#define tamanho_da_heap 10

///Troca valores de 2 variaveis
void troca(int *valor1, int *valor2){
	*valor1^=*valor2;
	*valor2^=*valor1;
	*valor1^=*valor2;
}

///Retorna um vetor que indica a heap
int* cria_heap(int tamanho){
	int *heap = (int*)calloc(sizeof(int),tamanho);//Inicializa tudo com zero
	return heap;
}

///Faz uma heap mínima
void heap_reconstroi_minima(int *heap, int tamanho){
	int i;
	for(i = (int)tamanho/2; i>-1; i--){ //Partindo da metade do vetor
		if(i*2+1 < tamanho && heap[i] > heap[i*2+1]){ ///Verifica se os filhos impares são menores
			troca(&heap[i],&heap[i*2+1]);
		}
		if(i*2+2 < tamanho && heap[i] > heap[i*2+2]){ ///Verifica se os filhos pares são menores
			troca(&heap[i],&heap[i*2+2]);
		}
	}
}

///Faz uma heap máxima
void heap_reconstroi_maxima(int *heap, int tamanho){
	int i;
	for(i = (int)tamanho/2; i>-1; i--){ //Partindo da metade do vetor
		if(i*2+1 < tamanho && heap[i] < heap[i*2+1]){ ///Verifica se os filhos impares são maiores
			troca(&heap[i],&heap[i*2+1]);
		}
		if(i*2+2 < tamanho && heap[i] < heap[i*2+2]){ ///Verifica se os filhos pares são maiores
			troca(&heap[i],&heap[i*2+2]);
		}
	}
}

///Gera qualquer valor para teste
void define_valores(int *heap, int tamanho){
	int i;
	for(i = 0; i < tamanho; i++){
		heap[i] = tamanho-i;
	}
}

///Exibe o vetor que representa a heap
void mostra_heap(int *heap, int tamanho){
	int i;
	for(i = 0; i < tamanho; i++){
		printf("%d ",heap[i]);
	}printf("\n");
}

int main(){
	int *heap = cria_heap(tamanho_da_heap);

	///Gera um valor inicial e o exibe
	define_valores(heap,tamanho_da_heap);
	mostra_heap(heap,tamanho_da_heap);
	printf("-----------------------\n");

	///Realiza o heapsort para testar
	int i;
	for(i = tamanho_da_heap; i > 0; i--){
		heap_reconstroi_maxima(heap,i);
		mostra_heap(heap,tamanho_da_heap);
		troca(&heap[0],&heap[i-1]);
	}
	
	return 0;
}
