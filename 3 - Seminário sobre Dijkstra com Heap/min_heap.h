#ifndef MIN_HEAP_H
#define MIN_HEAP_H

typedef struct {
    int vertex;
    int distance;
} HeapNode;

typedef struct {
    HeapNode* nodes;
    int capacity;
    int size;
    int* position; 
} MinHeap;

MinHeap* create_min_heap(int capacity);
void insert_node(MinHeap* heap, int vertex, int distance);
HeapNode extract_min(MinHeap* heap);
void decrease_key(MinHeap* heap, int vertex, int distance);
int is_empty(MinHeap* heap);
void free_min_heap(MinHeap* heap);

#endif
