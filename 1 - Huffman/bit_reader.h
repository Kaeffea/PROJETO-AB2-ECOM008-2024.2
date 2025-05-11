#ifndef BIT_READER_H
#define BIT_READER_H

#include <stdio.h>

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

void init_bit_reader(BitReader* reader, FILE* file);

int read_bit(BitReader* reader);

#endif
