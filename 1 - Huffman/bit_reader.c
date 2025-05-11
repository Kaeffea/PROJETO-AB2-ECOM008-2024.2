#include <stdio.h>
#include <stdlib.h>

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

void init_bit_reader(BitReader* reader, FILE* file) {
    reader->file = file;
    reader->buffer = 0;
    reader->bits_remaining = 0;
}

int read_bit(BitReader* reader) {
    if (reader->bits_remaining == 0) {
        int byte = fgetc(reader->file);
        if (byte == EOF) return -1;
        reader->buffer = byte;
        reader->bits_remaining = 8;
    }
    return (reader->buffer >> (--reader->bits_remaining)) & 1;
}