#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <stdio.h>

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

/**
 * @brief Cria um novo nó da árvore de Huffman.
 * 
 * @param byte Ponteiro para o byte representado (NULL para nós internos)
 * @param freq Ponteiro para a frequência (int*)
 * @param left Filho esquerdo (HuffmanNode*)
 * @param right Filho direito (HuffmandNode*)
 * @return Ponteiro para o novo HuffmanNode
 */
HuffmanNode* create_node(void* data);

/**
 * @brief Constrói a Min Heap com os bytes e suas frequências.
 *
 * @param freq Vetor de 256 posições com frequência dos bytes
 * @return MinHeap com os nós folha da árvore de Huffman
 */
MinHeap* build_heap_from_freq(int* freq);

/**
 * @brief Constrói a árvore de Huffman com base nas frequências dos bytes.
 * 
 * @param heap Heap já construída com nós
 * @return HuffmanNode* Raiz da árvore de Huffman
 */
HuffmanNode* build_huffman_tree(MinHeap* heap);

/**
 * @brief Função auxiliar recursiva para gerar os códigos da árvore de Huffman.
 * 
 * @param node Nó atual da árvore
 * @param current_code Código acumulado até aqui
 * @param codes Vetor de 256 ponteiros para string de bits
 */
void generate_codes_recursive(HuffmanNode* node, char* buffer, int depth, char** codes);

/**
 * @brief Gera os códigos de Huffman para cada byte da árvore.
 * 
 * @param root Raiz da árvore de Huffman
 * @param codes Vetor de 256 ponteiros para string, onde serão armazenados os códigos
 */
void generate_codes(HuffmanNode* root, char** codes);

/**
 * @brief Serializa a árvore de Huffman em pré-ordem com escape.
 * 
 * @param node Raiz da árvore.
 * @param output Arquivo de saída.
 * @param size Ponteiro para contador do tamanho da árvore (em bytes).
 */
void serialize_tree(HuffmanNode* node, FILE* output, int* size);

void free_huffman_tree(HuffmanNode* node);

void traverse_tree(HuffmanNode* node, char* buffer, int depth, char** codes);

#endif
