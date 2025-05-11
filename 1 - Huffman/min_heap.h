#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

/**
 * @brief Cria uma nova Min Heap.
 * 
 * @param capacity Capacidade inicial
 * @param cmp Função de comparação
 * @return Ponteiro para a nova Min Heap
 */
MinHeap* create_min_heap(int capacity, CompareFunc cmp);

/**
 * @brief Insere um elemento na Min Heap.
 * 
 * @param heap Ponteiro para a Min Heap
 * @param element Elemento a ser inserido
 */
void insert_heap(MinHeap* heap, void* element);

/**
 * @brief Remove e retorna o menor elemento da Min Heap.
 * 
 * @param heap Ponteiro para a Min Heap
 * @return Elemento removido
 */
void* remove_min(MinHeap* heap);

/**
 * @brief Libera a memória da Min Heap.
 * 
 * Obs: não libera os elementos, apenas o heap.
 */
void free_heap(MinHeap* heap);

#endif