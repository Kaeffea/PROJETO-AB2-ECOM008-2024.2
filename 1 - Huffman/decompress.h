#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

HuffmanNode* read_tree(FILE* in, int* remaining);

void decompress(const char* input_filename, const char* output_filename);

#endif