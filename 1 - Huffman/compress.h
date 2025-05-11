#ifndef COMPRESS_H
#define COMPRESS_H

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
 * @brief Escreve o cabeçalho no arquivo compactado (.huff)
 * 
 * @param output Arquivo .huff
 * @param trash_size Bits de lixo no final da compactação (0 a 7)
 * @param tree_size Tamanho da árvore serializada (em bytes)
 */
void write_header(FILE* output, int trash_size, int tree_size);

/**
 * @brief Escreve os bits de um código no buffer e salva no arquivo quando o buffer completa 8 bits.
 * 
 * @param output Arquivo .huff
 * @param code Código de Huffman (string de '0' e '1')
 * @param byte_buffer Buffer que guarda os bits temporariamente
 * @param bit_index Índice atual no buffer (vai de 7 até 0)
 */
void write_bits(FILE* output, const char* code, unsigned char* byte_buffer, int* bit_index);

/**
 * @brief Escreve os bits codificados no arquivo .huff e retorna o tamanho do lixo.
 * 
 * @param input Arquivo original
 * @param output Arquivo compactado
 * @param codes Vetor com os códigos de Huffman de cada byte
 * @return Número de bits de lixo
 */
int write_compressed_data(FILE* input, FILE* output, char* codes[256]);

#endif
