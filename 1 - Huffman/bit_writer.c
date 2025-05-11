#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

void init_bit_writer(BitWriter* writer, FILE* file) {
    writer->file = file;
    writer->buffer = 0;
    writer->bit_count = 0;
}

void write_bit(BitWriter* writer, int bit) {
    if (bit)
        writer->buffer |= (1 << (7 - writer->bit_count));
    
    writer->bit_count++;
    
    if (writer->bit_count == 8) {
        fputc(writer->buffer, writer->file);
        writer->buffer = 0;
        writer->bit_count = 0;
    }
}

void flush_bits(BitWriter* writer) {
    if (writer->bit_count > 0) {
        fputc(writer->buffer, writer->file);
        writer->buffer = 0;
        writer->bit_count = 0;
    }
}