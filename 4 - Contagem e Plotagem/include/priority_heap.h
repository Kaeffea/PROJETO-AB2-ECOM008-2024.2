#ifndef PRIORITY_HEAP_H
#define PRIORITY_HEAP_H

#include "structs.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

MinHeap* create_priority_heap(int capacidade);

void insert_heap(MinHeap* heap, void* dados, int prioridade);

PriorityItem* remove_min_heap(MinHeap* heap);

PriorityItem* peek_min_heap(MinHeap* heap);

void free_priority_heap(MinHeap* heap, void (*free_data)(void*));

#endif