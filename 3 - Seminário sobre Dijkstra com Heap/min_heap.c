#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "min_heap.h"

static void swap_nodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_down(MinHeap* heap, int i) {
    int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < heap->size && heap->nodes[left].distance < heap->nodes[smallest].distance)
        smallest = left;
    if (right < heap->size && heap->nodes[right].distance < heap->nodes[smallest].distance)
        smallest = right;

    if (smallest != i) {
        heap->position[heap->nodes[i].vertex] = smallest;
        heap->position[heap->nodes[smallest].vertex] = i;
        swap_nodes(&heap->nodes[i], &heap->nodes[smallest]);
        heapify_down(heap, smallest);
    }
}

static void heapify_up(MinHeap* heap, int i) {
    while (i && heap->nodes[i].distance < heap->nodes[(i - 1) / 2].distance) {
        heap->position[heap->nodes[i].vertex] = (i - 1) / 2;
        heap->position[heap->nodes[(i - 1) / 2].vertex] = i;
        swap_nodes(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

MinHeap* create_min_heap(int capacity) {
    MinHeap* heap = malloc(sizeof(MinHeap));
    heap->nodes = malloc(capacity * sizeof(HeapNode));
    heap->position = malloc(capacity * sizeof(int));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void insert_node(MinHeap* heap, int vertex, int distance) {
    heap->nodes[heap->size].vertex = vertex;
    heap->nodes[heap->size].distance = distance;
    heap->position[vertex] = heap->size;
    heapify_up(heap, heap->size++);
}

HeapNode extract_min(MinHeap* heap) {
    HeapNode root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[--heap->size];
    heap->position[heap->nodes[0].vertex] = 0;
    heapify_down(heap, 0);
    return root;
}

void decrease_key(MinHeap* heap, int vertex, int distance) {
    int i = heap->position[vertex];
    heap->nodes[i].distance = distance;
    heapify_up(heap, i);
}

int is_empty(MinHeap* heap) {
    return heap->size == 0;
}

void free_min_heap(MinHeap* heap) {
    free(heap->nodes);
    free(heap->position);
    free(heap);
}
