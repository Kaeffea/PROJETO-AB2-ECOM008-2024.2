#include "structs.h"
#include "priority_list_unsorted.h"
#include "priority_heap.h"
#include "metrics.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void init_list(PriorityList* lista){
    lista->inicio = NULL;
    lista->tamanho = 0;
}

void insert_unsorted(PriorityList* lista, void* dados, int prioridade){
    if (!lista) return;
    
    PriorityItem* item = malloc(sizeof(PriorityItem));
    if (!item) return;
    
    item->dados = dados;
    item->prioridade = prioridade;

    Node* no = malloc(sizeof(Node));
    if (!no) {
        free(item);
        return;
    }
    
    no->item = item;
    no->proximo = lista->inicio;
    lista->inicio = no;
    lista->tamanho++;
}

PriorityItem* remove_min_unsorted(PriorityList* lista){
    if (!lista || lista->inicio == NULL) return NULL;

    Node *atual = lista->inicio, *anterior = NULL;
    Node *menor = atual, *menor_anterior = NULL;

    while (atual) {
        increment_comparisons();
        if (atual->item->prioridade < menor->item->prioridade) {
            menor = atual;
            menor_anterior = anterior;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    if (menor_anterior) {
        menor_anterior->proximo = menor->proximo;
    } else {
        lista->inicio = menor->proximo;
    }

    PriorityItem* item = menor->item;
    free(menor);
    lista->tamanho--;

    return item;
}

void free_list(PriorityList* lista, void (*free_data)(void*)) {
    if (!lista) return;
    
    Node* atual = lista->inicio;
    while (atual) {
        Node* temp = atual;
        atual = atual->proximo;
        
        // Só libera dados se explicitamente pedido
        if (free_data && temp->item) {
            free_data(temp->item->dados);
        }
        free(temp->item);
        free(temp);
    }
    
    lista->inicio = NULL;
    lista->tamanho = 0;
}