#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

typedef struct huffman_node HuffmanNode;

/**
 * @brief Função de contagem usada pelo compressor.
 * 
 * Conta a frequência de cada byte em um arquivo (Ex: freq[A] = 4, freq[B] = 3, etc.).
 * 
 * @param file Ponteiro para o arquivo aberto em modo binário.
 * @param freq Array de 256 inteiros onde as frequências serão armazenadas.
 */
void count_frequencies(FILE* file, int freq[256]);

/**
 * @brief Função de comparação usada pela Min Heap.
 * 
 * Compara dois nós Huffman pela frequência.
 * 
 * @param a Ponteiro genérico para HuffmanNode.
 * @param b Ponteiro genérico para HuffmanNode.
 * @return Negativo se a < b, positivo se a > b, zero se iguais.
 */
int compare_freq(void* a, void* b);

/**
 * @brief Função para trocar o endereço entre dois ponteiros.
 * 
 * Usa uma variável temp para realizar a troca.
 * 
 * @param a Primeiro ponteiro.
 * @param b Segundo ponteiro.
 */
void swap(void** a, void** b);

int is_leaf(HuffmanNode* node);

void compress_file(const char* input_path, const char* output_path);

void decompress_file(const char* input_path, const char* output_path);

#endif
