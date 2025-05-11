#include <stdio.h>
#include <stdint.h>

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

void write_header(FILE* output, int trash_size, int tree_size) {
    trash_size &= 0x07;  // Garante apenas 3 bits
    tree_size &= 0x1FFF; // Garante apenas 13 bits
    uint16_t header = (trash_size << 13) | tree_size;
    fputc((header >> 8) & 0xFF, output);
    fputc(header & 0xFF, output);
}

void write_bits(FILE* output, const char* code, unsigned char* byte_buffer, int* bit_index) {
    for (int i = 0; code[i] != '\0'; i++) {
        if (code[i] == '1') {
            *byte_buffer |= (1 << *bit_index);
        }
        (*bit_index)--;

        if (*bit_index < 0) {
            fputc(*byte_buffer, output);
            *byte_buffer = 0;
            *bit_index = 7;
        }
    }
}

int write_compressed_data(FILE* input, FILE* output, char* codes[256]) {
    BitWriter writer;
    init_bit_writer(&writer, output);
    int trash_bits = 0;

    rewind(input);
    
    // Apenas um caractere repetido
    int unique_char = -1;
    for (int i = 0; i < 256; i++) {
        if (codes[i] != NULL) {
            if (unique_char == -1) {
                unique_char = i;
            } else {
                unique_char = -2; // Múltiplos caracteres
                break;
            }
        }
    }

    if (unique_char >= 0) {
        // Arquivo com apenas um caractere repetido
        int byte;
        while ((byte = fgetc(input)) != EOF) {
            write_bit(&writer, 1); // Escreve 1 para cada ocorrência
        }
    } else {
        // Processamento normal para múltiplos caracteres
        int byte;
        while ((byte = fgetc(input)) != EOF) {
            char* code = codes[byte];
            for (int i = 0; code[i] != '\0'; i++) {
                write_bit(&writer, code[i] == '1');
            }
        }
    }

    trash_bits = writer.bit_count > 0 ? 8 - writer.bit_count : 0;
    flush_bits(&writer);
    
    return trash_bits;
}