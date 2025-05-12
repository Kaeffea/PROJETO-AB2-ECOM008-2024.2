#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#include "min_heap.h"

AdjListNode* create_node(int dest, int weight) {
    AdjListNode* node = malloc(sizeof(AdjListNode));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}

Graph* create_graph(int V) {
    Graph* graph = malloc(sizeof(Graph));
    graph->V = V;
    graph->array = malloc(V * sizeof(AdjListNode*));
    for (int i = 0; i < V; ++i)
        graph->array[i] = NULL;
    return graph;
}

void add_edge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* node = create_node(dest, weight);
    node->next = graph->array[src];
    graph->array[src] = node;

    node = create_node(src, weight); // grafo não direcionado
    node->next = graph->array[dest];
    graph->array[dest] = node;
}

/*
void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[V];
    MinHeap* heap = create_min_heap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        insert_node(heap, v, dist[v]);
    }

    dist[src] = 0;
    decrease_key(heap, src, 0);

    while (!is_empty(heap)) {
        HeapNode min_node = extract_min(heap);
        int u = min_node.vertex;

        AdjListNode* p = graph->array[u];
        while (p) {
            int v = p->dest;
            if (dist[u] != INT_MAX && p->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + p->weight;
                decrease_key(heap, v, dist[v]);
            }
            p = p->next;
        }
    }

    printf("Distâncias mínimas a partir do vértice %d:\n", src);
    for (int i = 0; i < V; ++i)
        printf("Para %d: %d\n", i, dist[i]);

    free_min_heap(heap);
}
*/

void free_graph(Graph* graph) {
    for (int i = 0; i < graph->V; ++i) {
        AdjListNode* node = graph->array[i];
        while (node) {
            AdjListNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}
