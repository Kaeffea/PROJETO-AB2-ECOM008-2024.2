#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

HuffmanNode* read_tree(FILE* in, int* remaining) {
    if (*remaining <= 0) return NULL;

    int byte = fgetc(in);
    (*remaining)--;

    if (byte == EOF) return NULL;

    HuffmanNode* node = malloc(sizeof(HuffmanNode));
    node->left = node->right = NULL;
    node->data = NULL;

    if (byte == '\\') {
        // Caractere escapado
        byte = fgetc(in);
        (*remaining)--;
        
        if (byte == EOF) {
            free(node);
            return NULL;
        }

        HuffmanData* data = malloc(sizeof(HuffmanData));
        data->byte = byte;
        data->freq = 0;
        node->data = data;
        return node;
    }

    if (byte == '*') {
        // Nó interno
        node->left = read_tree(in, remaining);
        node->right = read_tree(in, remaining);
        return node;
    }

    // Folha normal
    HuffmanData* data = malloc(sizeof(HuffmanData));
    data->byte = byte;
    data->freq = 0;
    node->data = data;
    return node;
}

void decompress(const char* input_filename, const char* output_filename) {
    FILE* in = fopen(input_filename, "rb");
    if (!in) {
        perror("Erro ao abrir arquivo de entrada");
        return;
    }

    FILE* out = fopen(output_filename, "wb");
    if (!out) {
        perror("Erro ao abrir arquivo de saída");
        fclose(in);
        return;
    }

    // Verifica se o arquivo está vazio
    fseek(in, 0, SEEK_END);
    long file_size = ftell(in);
    rewind(in);

    if (file_size == 0) {
        fclose(in);
        fclose(out);
        return;
    }

    // Lê cabeçalho (2 bytes)
    int byte1 = fgetc(in);
    int byte2 = fgetc(in);
    if (byte1 == EOF || byte2 == EOF) {
        fclose(in);
        fclose(out);
        fprintf(stderr, "Arquivo de entrada inválido\n");
        return;
    }

    int trash_size = byte1 >> 5;
    int tree_size = ((byte1 & 0x1F) << 8) | byte2;

    // Reconstroi a árvore
    int remaining = tree_size;
    HuffmanNode* root = read_tree(in, &remaining);
    if (!root) {
        fclose(in);
        fclose(out);
        fprintf(stderr, "Erro ao reconstruir a árvore de Huffman\n");
        return;
    }

    // Caso especial: arquivo com apenas um caractere
    if (tree_size == 1 && is_leaf(root)) {
        HuffmanData* data = (HuffmanData*)root->data;
        if (!data) {
            fclose(in);
            fclose(out);
            free_huffman_tree(root);
            return;
        }

        // Lê os dados bit a bit
        BitReader reader;
        init_bit_reader(&reader, in);
        
        while (1) {
            int bit = read_bit(&reader);
            if (bit == -1) break;
            if (bit == 1) {  // Ignora 0s, só escreve para 1s
                fputc(data->byte, out);
            }
        }
    } else {
        // Processamento normal para múltiplos caracteres
        BitReader reader;
        init_bit_reader(&reader, in);
        
        // Calcula quantos bits devem ser processados
        long data_start = ftell(in);
        fseek(in, 0, SEEK_END);
        long total_bytes = ftell(in) - data_start;
        fseek(in, data_start, SEEK_SET);
        int total_bits = (total_bytes * 8) - trash_size;
        
        HuffmanNode* current = root;
        int bits_processed = 0;
        
        while (bits_processed < total_bits) {
            int bit = read_bit(&reader);
            if (bit == -1) break;
            
            bits_processed++;
            current = bit ? current->right : current->left;
            
            if (!current) {
                fprintf(stderr, "Erro: caminho inválido na árvore\n");
                break;
            }
            
            if (is_leaf(current)) {
                HuffmanData* data = (HuffmanData*)current->data;
                if (data) {
                    fputc(data->byte, out);
                }
                current = root;
            }
        }
    }

    fclose(in);
    fclose(out);
    free_huffman_tree(root);
}