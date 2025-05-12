#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#include "min_heap.h"

#define GREEN   "\033[1;32m"
#define BLUE    "\033[1;34m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"
#define RED     "\033[1;31m"

void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int* dist = malloc(V * sizeof(int));
    int* visited = calloc(V, sizeof(int));
    MinHeap* minHeap = create_min_heap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INT_MAX;
        insert_node(minHeap, v, INT_MAX);
    }

    dist[src] = 0;
    decrease_key(minHeap, src, 0);

    while (!is_empty(minHeap)) {
        HeapNode min_node = extract_min(minHeap);
        int u = min_node.vertex;
        visited[u] = 1;

        for (AdjListNode* neighbor = graph->array[u]; neighbor != NULL; neighbor = neighbor->next) {
            int v = neighbor->dest;
            int weight = neighbor->weight;

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                decrease_key(minHeap, v, dist[v]);
            }
        }
    }

    printf(GREEN "----------------------------------------\n" RESET);
    printf(YELLOW "    Vértice    |    Distância de %d\n" RESET, src);
    printf(GREEN "----------------------------------------\n" RESET);
    for (int i = 0; i < V; i++) {
        printf("       %2d      |      ", i);
        if (dist[i] == INT_MAX)
            printf(RED "Infinito\n" RESET);
        else
            printf(BLUE "%d\n" RESET, dist[i]);
    }
    printf(GREEN "----------------------------------------\n" RESET);

    free(dist);
    free(visited);
    free_min_heap(minHeap);
}
