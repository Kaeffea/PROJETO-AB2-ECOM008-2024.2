#ifndef GRAPH_H
#define GRAPH_H

typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

typedef struct {
    int V;
    AdjListNode** array;
} Graph;

Graph* create_graph(int V);
void add_edge(Graph* graph, int src, int dest, int weight);
void dijkstra(Graph* graph, int src);
void free_graph(Graph* graph);

#endif
