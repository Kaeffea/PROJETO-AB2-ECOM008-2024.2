#include <stdlib.h>
#include <string.h>

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

HuffmanNode* create_node(void* data) {
    HuffmanNode* node = malloc(sizeof(HuffmanNode));
    if (!node) return NULL;
    
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
HuffmanData* create_data(unsigned char byte, int freq) {
    HuffmanData* data = malloc(sizeof(HuffmanData));
    data->byte = byte;
    data->freq = freq;
    return data;
}

MinHeap* build_heap_from_freq(int* freq) {
    MinHeap* heap = create_min_heap(256, compare_freq);
    if (!heap) return NULL;

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            HuffmanData* data = (HuffmanData*)malloc(sizeof(HuffmanData));
            if (!data) {
                free_heap(heap);
                return NULL;
            }
            data->byte = i;
            data->freq = freq[i];

            HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
            if (!node) {
                free(data);
                free_heap(heap);
                return NULL;
            }
            node->data = data;
            node->left = NULL;
            node->right = NULL;

            insert_heap(heap, (void*)node);
        }
    }
    return heap;
}

HuffmanNode* build_huffman_tree(MinHeap* heap) {

    while (heap->size > 1) {
        HuffmanNode* left = (HuffmanNode*)remove_min(heap);
        HuffmanNode* right = (HuffmanNode*)remove_min(heap);

        // Cria novo nó interno
        HuffmanData* new_data = (HuffmanData*)malloc(sizeof(HuffmanData));
        if (!new_data) {
            free_huffman_tree(left);
            free_huffman_tree(right);
            return NULL;
        }
        new_data->byte = 0;
        new_data->freq = ((HuffmanData*)left->data)->freq + ((HuffmanData*)right->data)->freq;

        HuffmanNode* internal_node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
        if (!internal_node) {
            free(new_data);
            free_huffman_tree(left);
            free_huffman_tree(right);
            return NULL;
        }
        internal_node->data = new_data;
        internal_node->left = left;
        internal_node->right = right;

        insert_heap(heap, (void*)internal_node);
    }

    return (HuffmanNode*)remove_min(heap);
}

void generate_codes_recursive(HuffmanNode* node, char* buffer, int depth, char** codes) {
    if (!node || depth >= 255) return;

    if (is_leaf(node)) {
        HuffmanData* data = (HuffmanData*)node->data;
        if (data) {
            codes[data->byte] = strdup(buffer);
        }
        return;
    }

    buffer[depth] = '0';
    generate_codes_recursive(node->left, buffer, depth + 1, codes);
    
    buffer[depth] = '1';
    generate_codes_recursive(node->right, buffer, depth + 1, codes);
    
    buffer[depth] = '\0';
}

void generate_codes(HuffmanNode* root, char** codes) {
    if (root == NULL) return;  // Verificação adicional
    
    char buffer[256] = {0};
    traverse_tree(root, buffer, 0, codes);
}

void traverse_tree(HuffmanNode* node, char* buffer, int depth, char** codes) {
    if (!node || depth >= 255) return;  // Verificação de segurança
    
    if (is_leaf(node)) {
        HuffmanData* data = (HuffmanData*)node->data;
        if (data) {  // Verificação adicional
            buffer[depth] = '\0';
            codes[data->byte] = strdup(buffer);
        }
        return;
    }
    
    buffer[depth] = '0';
    traverse_tree(node->left, buffer, depth + 1, codes);
    
    buffer[depth] = '1';
    traverse_tree(node->right, buffer, depth + 1, codes);
}

void serialize_tree(HuffmanNode* node, FILE* output, int* size) {
    if (!node) return;

    if (is_leaf(node)) {
        HuffmanData* data = (HuffmanData*)node->data;
        unsigned char c = data->byte;
        
        if (c == '*' || c == '\\') {
            fputc('\\', output);
            (*size)++;
        }
        fputc(c, output);
        (*size)++;
    } else {
        fputc('*', output);
        (*size)++;
        serialize_tree(node->left, output, size);
        serialize_tree(node->right, output, size);
    }
}

void free_huffman_tree(HuffmanNode* node) {
    if (!node) return;
    
    free_huffman_tree(node->left);
    free_huffman_tree(node->right);
    
    if (node->data) {
        free(node->data);
    }
    
    free(node);
}