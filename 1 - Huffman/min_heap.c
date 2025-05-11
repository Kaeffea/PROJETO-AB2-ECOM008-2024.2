#include <stdlib.h>

#include "compress.h"
#include "bit_writer.h"
#include "bit_reader.h"
#include "decompress.h"
#include "huffman_tree.h"
#include "min_heap.h"
#include "structs.h"
#include "utils.h"

MinHeap* create_min_heap(int capacity, CompareFunc cmp) {

    MinHeap* heap = malloc(sizeof(MinHeap));
    if (!heap) return NULL;

    heap->data = malloc(sizeof(void*) * capacity);
    if (!heap->data) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    heap->cmp = cmp;
    return heap;
}

void insert_heap(MinHeap* heap, void* element) {
    if (heap->size == heap->capacity) return;

    int i = heap->size++;
    heap->data[i] = element;

    while (i > 0) {
        int parent = (i - 1) / 2;
        HuffmanNode* a = (HuffmanNode*)heap->data[i];
        HuffmanNode* b = (HuffmanNode*)heap->data[parent];
        
        if (heap->cmp(a, b) >= 0) break;
        
        void* temp = heap->data[i];
        heap->data[i] = heap->data[parent];
        heap->data[parent] = temp;
        
        i = parent;
    }
}

void* remove_min(MinHeap* heap) {
    if (heap->size == 0) return NULL;

    void* min = heap->data[0];
    heap->data[0] = heap->data[--heap->size];

    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size) {
            HuffmanNode* left_node = (HuffmanNode*)heap->data[left];
            HuffmanNode* current = (HuffmanNode*)heap->data[smallest];
            if (heap->cmp(left_node, current) < 0)
                smallest = left;
        }

        if (right < heap->size) {
            HuffmanNode* right_node = (HuffmanNode*)heap->data[right];
            HuffmanNode* current = (HuffmanNode*)heap->data[smallest];
            if (heap->cmp(right_node, current) < 0)
                smallest = right;
        }

        if (smallest == i) break;

        void* temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;
        
        i = smallest;
    }

    return min;
}

void free_heap(MinHeap* heap) {
    if (!heap) return;
    
    // Libera todos os nós primeiro (se necessário)
    for (int i = 0; i < heap->size; i++) {
        HuffmanNode* node = (HuffmanNode*)heap->data[i];
        free_huffman_tree(node);
    }
    
    free(heap->data);
    free(heap);
}