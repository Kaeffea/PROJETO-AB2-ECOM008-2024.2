#ifndef STRUCTS_H
#define STRUCTS_H

/**
 * @brief Tipo de função para comparar dois elementos genéricos.
 * Deve retornar negativo se a < b, 0 se a == b, positivo se a > b.
 */
typedef int (*CompareFunc)(void* a, void* b);

typedef struct {
    unsigned char byte;
    int freq;
} HuffmanData;

/**
 * @brief Estrutura que representa um nó da árvore de Huffman.
 * 
 * Cada nó pode ser uma folha (com byte) ou um nó interno (com filhos).
 */
typedef struct huffman_node {
    void* data;  // HuffmanData* (como void*)
    struct huffman_node* left;  // Tipo concreto
    struct huffman_node* right; // Tipo concreto
} HuffmanNode;

/**
 * @brief Estrutura de uma Min Heap genérica.
 */
typedef struct min_heap {
    void** data;     // Array de HuffmanNode* (como void*)
    int size;        // Tipo concreto
    int capacity;    // Tipo concreto
    CompareFunc cmp; // Ponteiro de função normal
} MinHeap;

typedef struct {
    FILE* file;
    unsigned char buffer;
    int bit_count;
} BitWriter;

typedef struct {
    FILE* file;
    unsigned char buffer;
    int bits_remaining;
} BitReader;

#endif