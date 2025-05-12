#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

// Estrutura auxiliar para geração de arestas sem repetição
typedef struct {
    int u, v;
} Aresta;

void print_menu() {
    printf(BLUE "=====================================\n" RESET);
    printf(GREEN "         ALGORITMO DE DIJKSTRA       \n" RESET);
    printf(BLUE "=====================================\n" RESET);
    printf(YELLOW "1. Gerar grafo aleatório e rodar Dijkstra\n");
    printf("2. Sair\n" RESET);
    printf(BLUE "=====================================\n" RESET);
    printf("Escolha uma opção: ");
}

int main() {
    srand(time(NULL));
    int opcao;

    while (1) {
        print_menu();
        scanf("%d", &opcao);

        if (opcao == 1) {
            int V, E;
            printf(GREEN "\nDigite o número de vértices do grafo: " RESET);
            scanf("%d", &V);

            printf(GREEN "Digite o número de arestas: " RESET);
            scanf("%d", &E);

            int max_arestas = V * (V - 1);
            if (E > max_arestas) {
                printf(RED "Erro: máximo de arestas em grafo dirigido sem paralelas é %d\n\n" RESET, max_arestas);
                continue;
            }

            Graph* graph = create_graph(V);

            printf(YELLOW "\nGerando %d arestas aleatórias...\n" RESET, E);

            // Gera todas arestas possíveis sem laço
            Aresta* possiveis = malloc(max_arestas * sizeof(Aresta));
            int total = 0;
            for (int u = 0; u < V; u++) {
                for (int v = 0; v < V; v++) {
                    if (u != v) {
                        possiveis[total].u = u;
                        possiveis[total].v = v;
                        total++;
                    }
                }
            }

            // Embaralha
            for (int i = total - 1; i > 0; i--) {
                int j = rand() % (i + 1);
                Aresta tmp = possiveis[i];
                possiveis[i] = possiveis[j];
                possiveis[j] = tmp;
            }

            // Adiciona as E primeiras
            for (int i = 0; i < E; i++) {
                int u = possiveis[i].u;
                int v = possiveis[i].v;
                int peso = 1 + rand() % 20;
                add_edge(graph, u, v, peso);
                printf("  - Aresta gerada: %d → %d (peso %d)\n", u, v, peso);
            }

            free(possiveis);

            int origem;
            printf(GREEN "\nDigite o vértice de origem para Dijkstra: " RESET);
            scanf("%d", &origem);

            if (origem < 0 || origem >= V) {
                printf(RED "Vértice inválido!\n\n" RESET);
                free_graph(graph);
                continue;
            }

            printf(BLUE "\nCalculando menores distâncias usando Dijkstra...\n\n" RESET);
            dijkstra(graph, origem);

            free_graph(graph);
            printf(GREEN "\nPressione ENTER para voltar ao menu..." RESET);
            getchar(); getchar();

        } else if (opcao == 2) {
            printf(RED "\nSaindo...\n" RESET);
            break;
        } else {
            printf(RED "Opção inválida! Tente novamente.\n\n" RESET);
        }
    }

    return 0;
}

/*
Executar em Linux: make clean && make && ./dijkstra
Executar em Windows: make clean ; make ; ./dijkstra.exe
*/
