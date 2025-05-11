#ifndef BIT_WRITER_H
#define BIT_WRITER_H

#include <stdio.h>

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

void init_bit_writer(BitWriter* writer, FILE* file);

void write_bit(BitWriter* writer, int bit);

void flush_bits(BitWriter* writer);

#endif
