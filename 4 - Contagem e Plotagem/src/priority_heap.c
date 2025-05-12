#include "structs.h"
#include "priority_list_unsorted.h"
#include "priority_heap.h"
#include "metrics.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

MinHeap* create_priority_heap(int capacidade){
    if (capacidade <= 0) return NULL;
    
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    
    heap->itens = (PriorityItem**) malloc(sizeof(PriorityItem*) * capacidade);
    if (!heap->itens) {
        free(heap);
        return NULL;
    }
    
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    return heap;
}

static void swap(PriorityItem** a, PriorityItem** b){
    PriorityItem* temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_down(MinHeap* heap, int indice) {
    while (1) {
        int esquerda = 2 * indice + 1;
        int direita = 2 * indice + 2;
        int menor = indice;

        increment_comparisons(); // Conta a verificação inicial do loop
        
        if (esquerda < heap->tamanho) {
            increment_comparisons();
            if (heap->itens[esquerda]->prioridade < heap->itens[menor]->prioridade) {
                menor = esquerda;
            }
        }

        if (direita < heap->tamanho) {
            increment_comparisons();
            if (heap->itens[direita]->prioridade < heap->itens[menor]->prioridade) {
                menor = direita;
            }
        }

        increment_comparisons(); // Conta a comparação (menor != indice)
        if (menor != indice) {
            swap(&heap->itens[indice], &heap->itens[menor]);
            indice = menor;
        } else {
            break;
        }
    }
}

static void heapify_up(MinHeap* heap, int indice) {
    while (indice > 0) {
        int pai = (indice - 1) / 2;
        
        increment_comparisons(); // Comparação de prioridades real
        if (heap->itens[indice]->prioridade < heap->itens[pai]->prioridade) {
            swap(&heap->itens[indice], &heap->itens[pai]);
            indice = pai;
        } else {
            break;
        }
    }
}

void insert_heap(MinHeap* heap, void* dados, int prioridade){
    if (!heap || !dados) return;
    
    if(heap->tamanho == heap->capacidade){
        size_t new_capacity = heap->capacidade * 2;
        PriorityItem** new_itens = (PriorityItem**) realloc(heap->itens, 
                                  sizeof(PriorityItem*) * new_capacity);
        if (!new_itens) return; // Falha no realloc
        
        heap->itens = new_itens;
        heap->capacidade = new_capacity;
    }

    PriorityItem* novo = (PriorityItem*) malloc(sizeof(PriorityItem));
    if (!novo) return;
    
    novo->dados = dados;
    novo->prioridade = prioridade;

    heap->itens[heap->tamanho] = novo;
    heapify_up(heap, heap->tamanho);
    heap->tamanho++;
}

PriorityItem* peek_min_heap(MinHeap* heap){
    if (heap->tamanho == 0) return NULL;
    return heap->itens[0];
}

PriorityItem* remove_min_heap(MinHeap* heap){
    if (heap->tamanho == 0) return NULL;

    PriorityItem* menor = heap->itens[0];
    heap->tamanho--;
    heap->itens[0] = heap->itens[heap->tamanho];
    heapify_down(heap, 0);
    return menor;
}

void free_priority_heap(MinHeap* heap, void (*free_data)(void*)) {
    if (!heap) return;
    
    // Libera apenas os itens ativos (até heap->tamanho)
    for (int i = 0; i < heap->tamanho; i++) {
        if (heap->itens[i]) {
            if (free_data) free_data(heap->itens[i]->dados);
            free(heap->itens[i]);
        }
    }
    
    // Libera o array de itens e a estrutura do heap
    free(heap->itens);
    free(heap);
}
