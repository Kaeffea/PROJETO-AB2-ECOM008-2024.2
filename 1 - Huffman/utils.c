#include <string.h>
#include <ctype.h>

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

void count_frequencies(FILE* file, int freq[256]) {
    unsigned char byte;
    size_t bytes_read;
    size_t total_bytes = 0;
    
    // Zera o array de frequências
    memset(freq, 0, sizeof(int) * 256);
    
    while ((bytes_read = fread(&byte, 1, 1, file)) == 1) {
        freq[byte]++;
        total_bytes++;
    }
    
    rewind(file);
}

int compare_freq(void* a, void* b) {
    HuffmanNode* nodeA = (HuffmanNode*)a;
    HuffmanNode* nodeB = (HuffmanNode*)b;
    
    HuffmanData* dataA = (HuffmanData*)(nodeA->data);
    HuffmanData* dataB = (HuffmanData*)(nodeB->data);
    
    return dataA->freq - dataB->freq;
}

void swap(void** a, void** b) {
    void* temp = *a;
    *a = *b;
    *b = temp;
}

int is_leaf(HuffmanNode* node) {
    return node->left == NULL && node->right == NULL;
}

void decompress_file(const char* input_path, const char* output_path) {
    FILE* in = fopen(input_path, "rb");
    FILE* out = fopen(output_path, "wb");
    
    if (!in || !out) {
        perror("Erro ao abrir arquivos");
        if (in) fclose(in);
        if (out) fclose(out);
    }

    decompress(input_path, output_path);
    
    fclose(in);
    fclose(out);
}

void compress_file(const char* input_path, const char* output_path) {
    // 1. Abrir arquivos
    FILE* input = fopen(input_path, "rb");
    FILE* output = fopen(output_path, "wb");

    // Verifica se o arquivo está vazio
    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    rewind(input);

    if (file_size == 0) {
        // Arquivo vazio - cria arquivo .huff vazio
        fclose(input);
        fclose(output);
        return;
    }

    // 2. Contar frequências
    int freq[256] = {0};
    count_frequencies(input, freq);

    // Verifica se há pelo menos um caractere com frequência > 0
    int valid_chars = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) valid_chars++;
    }

    if (valid_chars == 0) {
        fclose(input);
        fclose(output);
        return;
    }

    // 3. Construir árvore de Huffman
    MinHeap* heap = build_heap_from_freq(freq);

    HuffmanNode* root = build_huffman_tree(heap);
    char* codes[256] = {NULL};
    generate_codes(root, codes);

    // 5. Reservar espaço para cabeçalho
    if (fseek(output, 2, SEEK_SET) != 0) {
        perror("Erro ao posicionar arquivo");
        fclose(input);
        fclose(output);
    }

    // 6. Serializar árvore
    int tree_size = 0;
    serialize_tree(root, output, &tree_size);

    // 7. Comprimir dados
    int trash_size = write_compressed_data(input, output, codes);

    // 8. Escrever cabeçalho
    rewind(output);
    write_header(output, trash_size, tree_size);

    // 9. Liberar recursos
    if (root) {
        free_huffman_tree(root);
        root = NULL;
    }

    free_heap(heap);
    
    // Liberação segura dos códigos
    for (int i = 0; i < 256; i++) {
        if (codes[i]) {
            free(codes[i]);
            codes[i] = NULL;
        }
    }

    fclose(input);
    fclose(output);
}