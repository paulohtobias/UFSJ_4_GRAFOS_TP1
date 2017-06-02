#include <stdio.h>
#include <stdlib.h>

#ifndef TYPE_BOOL
#define TYPE_BOOL
	typedef int bool;
	#define false 0
	#define true 1
#endif //TYPE_BOOL

//Definição e operações com Nó.
typedef struct No_{
    struct No_ *anterior;
    void *dado;
    struct No_ *proximo;
}No;

//Cria um novo nó com os parâmetro passados.
No *novo_No(No *anterior, void *dado, No *proximo);

//Definição e operações com Lista.
typedef struct Lista_{
    size_t size;
    int tamanho;
    No *primeiro;
    No *ultimo;
}Lista;

//Cria uma nova lista vazia.
Lista *nova_Lista(size_t sizeof_dado);

//Verifica se a lista está vazia.
bool lista_vazia(Lista *lista);

//Insere um elemento ao final da lista.
void lista_insere_final(Lista *lista, void *dado);
