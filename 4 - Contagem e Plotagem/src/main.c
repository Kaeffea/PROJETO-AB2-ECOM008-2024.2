#include "structs.h"
#include "priority_list_unsorted.h"
#include "priority_heap.h"
#include "metrics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SCRIPTS_DIR "scripts"
#define INSERT_CSV "scripts/insercao.csv"
#define REMOVE_CSV "scripts/remocao.csv"

void create_scripts_dir() {
    // Check if scripts directory exists, if not create it
    if (access(SCRIPTS_DIR, F_OK) == -1) {
        #ifdef _WIN32
        mkdir(SCRIPTS_DIR);
        #else
        mkdir(SCRIPTS_DIR, 0777);
        #endif
    }
}

void print_menu() {
    printf("\033[1;33m"); // Yellow color
    printf("\n+-------------------------------------+\n");
    printf("|        MENU PRINCIPAL              |\n");
    printf("+-------------------------------------+\n");
    printf("| 1. Executar comparações            |\n");
    printf("| 2. Sair                            |\n");
    printf("+-------------------------------------+\n");
    printf("\033[0m");
    printf("Escolha uma opção: ");
}

void free_data(void* data) {
    free(data);
}

void run_comparisons(int n) {
    FILE *ins_fp = fopen(INSERT_CSV, "w");
    FILE *rem_fp = fopen(REMOVE_CSV, "w");
    
    if (!ins_fp || !rem_fp) {
        printf("Erro ao abrir arquivos CSV!\n");
        return;
    }
    
    // Write CSV headers
    fprintf(ins_fp, "tamanho,ins_heap_comp,ins_list_comp\n");
    fprintf(rem_fp, "tamanho,rem_heap_comp,rem_list_comp\n");
    
    srand(time(NULL));
    
    for (int i = 0; i < n; i++) {
        // Generate random size between 5 and 1000
        int size = 1 + rand() % 5000;
        
        // Create structures
        MinHeap* heap = create_priority_heap(size);
        PriorityList list;
        init_list(&list);
        
        // Fill structures with separate items (same values but different memory)
        for (int j = 0; j < size; j++) {
            // Use a controlled priority distribution (for example, increasing priorities)
            int priority = j; // Prioridades crescentes para evitar distorções
            int* heap_data = malloc(sizeof(int));
            int* list_data = malloc(sizeof(int));
            *heap_data = priority;
            *list_data = priority;
            
            insert_heap(heap, heap_data, priority);
            insert_unsorted(&list, list_data, priority);
        }

        // Test insertion with separate data items
        int new_priority = rand() % 1000;
        
        int* heap_new_data = malloc(sizeof(int));
        int* list_new_data = malloc(sizeof(int));
        *heap_new_data = new_priority;
        *list_new_data = new_priority;
        
        reset_comparisons();
        insert_heap(heap, heap_new_data, new_priority);
        int heap_ins_comp = get_comparisons();
        
        reset_comparisons();
        insert_unsorted(&list, list_new_data, new_priority);
        int list_ins_comp = get_comparisons();
        
        fprintf(ins_fp, "%d,%d,%d\n", size, heap_ins_comp, list_ins_comp);
        
        // Test removal
        reset_comparisons();
        PriorityItem* heap_item = remove_min_heap(heap);
        int heap_rem_comp = get_comparisons();
        if (heap_item) {
            free(heap_item->dados);
            free(heap_item);
        }
        
        reset_comparisons();
        PriorityItem* list_item = remove_min_unsorted(&list);
        int list_rem_comp = get_comparisons();
        if (list_item) {
            free(list_item->dados);
            free(list_item);
        }
        
        fprintf(rem_fp, "%d,%d,%d\n", size, heap_rem_comp, list_rem_comp);
        
        // Free structures
        free_priority_heap(heap, free_data);
        free_list(&list, free_data);
    }
    
    fclose(ins_fp);
    fclose(rem_fp);
    
    printf("\033[1;32m"); // Green color
    printf("\nDados salvos em:\n");
    printf("- %s\n", INSERT_CSV);
    printf("- %s\n", REMOVE_CSV);
    printf("\033[0m");
}

int main() {
    create_scripts_dir();
    
    int option;
    int n;
    
    while (1) {
        print_menu();
        
        if (scanf("%d", &option) != 1) {
            printf("\033[1;31m"); // Red color
            printf("Entrada inválida! Por favor, digite um número.\n");
            printf("\033[0m");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        
        switch (option) {
            case 1:
                printf("Quantas comparações deseja executar? ");
                if (scanf("%d", &n) != 1 || n <= 0) {
                    printf("\033[1;31m");
                    printf("Número inválido! Deve ser um inteiro positivo.\n");
                    printf("\033[0m");
                    while (getchar() != '\n');
                    continue;
                }
                run_comparisons(n);
                break;
            case 2:
                printf("\033[1;35m"); // Magenta color
                printf("Saindo... Até logo!\n");
                printf("\033[0m");
                return 0;
            default:
                printf("\033[1;31m");
                printf("Opção inválida! Tente novamente.\n");
                printf("\033[0m");
        }
    }
    
    return 0;
}

/*
Executar em Linux: make clean && make && ./pq && Rscript scripts/plot.R
Executar em Windows: make clean ; make ; ./pq.exe ; Rscript scripts/plot.R
*/
