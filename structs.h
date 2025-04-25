#ifndef STRUCTS_H
#define STRUCTS_H

#include "min_heap.h"

/**
 * @brief Estrutura que representa um nó da árvore de Huffman.
 * 
 * Cada nó pode ser uma folha (com byte) ou um nó interno (com filhos).
 * Todos os campos são ponteiros genéricos (void*) conforme exigência do projeto.
 */
typedef struct huffman_node{
    void* byte; // Ponteiro para o byte representado (unsigned char* em folhas)
    void* freq; // Ponteiro para a frequência (int*)
    void* left; // Ponteiro para o filho esquerdo (HuffmanNode*)
    void* right; // Ponteiro para o filho direito (HuffmanNode*)
} HuffmanNode;

/**
 * @brief Estrutura de uma Min Heap genérica.
 */
typedef struct min_heap {
    void** data;
    int size;
    int capacity;
    CompareFunc cmp;
} MinHeap;

#endif