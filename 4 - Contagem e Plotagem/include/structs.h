#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/**
 * Estrutura que representa um elemento de fila de prioridade.
 */
typedef struct{
    void* dados; // Ponteiro genérico para os dados do item.
    int prioridade; // Prioridade do item.
} PriorityItem;

// -------------------------------------------------------------------------------
// Estrutura da Fila de Prioridades SEM Heap.

/**
 * Estrutura que representa um nó de lista encadeada.
 */
typedef struct Node{
    PriorityItem* item; // Item armazenado no nó.
    struct Node* proximo; // Ponteiro para o próximo nó da lista.
} Node;

/**
 * Estrutura que representa a lista (ordenada ou desordenada).
 */
typedef struct{
    Node* inicio; // Ponteiro pro primeiro nó da lista.
    int tamanho;
} PriorityList;


// -------------------------------------------------------------------------------
// Estrutura da Fila de prioridade COM Heap.

typedef struct{
    PriorityItem** itens;
    int tamanho;
    int capacidade;
} MinHeap;

#endif