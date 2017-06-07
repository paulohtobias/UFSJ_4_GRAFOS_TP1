#include "lista.h"

//Operações com Nó.
//Cria um novo nó com os parâmetro passados.
No *novo_No(No *anterior, char *descricao, void *dado, No *proximo){
    No *no = malloc(sizeof(No));

    no->anterior = anterior;
    no->descricao = descricao;
    no->dado = dado;
    no->proximo = proximo;

    return no;
}

//Operações com Lista.
//Cria uma nova lista vazia.
Lista *nova_Lista(char *descricao){
    Lista *lista = malloc(sizeof (Lista));

    lista->tamanho = 0;
    lista->descricao = malloc(1 + strlen(descricao));
    strcpy(lista->descricao, descricao);
    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}
//Libera uma lista da memória.
void free_Lista(Lista *lista, void (*free_data)()){
    No *temp;

    for(temp = lista->primeiro; temp != NULL; temp = temp->proximo){
        free_data(temp->dado);
        lista->tamanho--;
    }
    lista->primeiro = lista->ultimo = NULL;

    free(lista);
}

//Verifica se a lista está vazia.
bool lista_vazia(Lista *lista){
    return (lista->tamanho == 0);
}

//Insere um elemento ao final da lista.
void lista_insere_final(Lista *lista, char *descricao, void *dado){
    No *no = novo_No(lista->ultimo, descricao, dado, NULL);

    if(lista_vazia(lista)){
        lista->primeiro = no;
    }else{
        lista->ultimo->proximo = no;
    }
    lista->ultimo = no;
    lista->tamanho++;
}
