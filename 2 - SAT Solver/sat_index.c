#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARS 100 // Número máximo de variáveis
#define MAX_CLAUSES 1000   // Número máximo de cláusulas

// Estrutura para armazenar cada cláusula
typedef struct {
    int* literals; // Vetor de inteiros com os literais da cláusula (ex: 1, -3, etc.)
    int size;      // Quantidade de literais na cláusula
} Clause;

int num_vars = 0;       // Quantidade de variáveis (do cabeçalho DIMACS)
int num_clauses = 0;    // Quantidade real de cláusulas lidas (idem)
Clause clauses[MAX_CLAUSES]; // Vetor com todas as cláusulas do problema

// Analisar e carregar o arquivo DIMACS CNF
int parse_dimacs(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    char line[256];
    int expected_clauses = 0;

    while (fgets(line, sizeof(line), file)) {
        // Ignora comentários
        if (line[0] == 'c') continue;

        // Linha do cabeçalho
        if (line[0] == 'p') {
            if (sscanf(line, "p cnf %d %d", &num_vars, &expected_clauses) != 2) {
                fprintf(stderr, "Erro no cabeçalho DIMACS\n");
                fclose(file);
                return 0;
            }
        } else if (line[0] == '\n' || line[0] == '\0') {
            continue;
        } else {
            if (num_clauses >= expected_clauses) continue; // Evita ler mais do que o especificado

            int temp[256];
            int count = 0, lit;

            // Lê literais até encontrar o 0 (fim da cláusula)
            char* ptr = strtok(line, " \n");
            while (ptr != NULL) {
                lit = atoi(ptr);
                if (lit == 0) break;
                temp[count++] = lit;
                ptr = strtok(NULL, " \n");
            }

            // Armazena a cláusula no vetor
            clauses[num_clauses].literals = malloc(sizeof(int) * count);
            memcpy(clauses[num_clauses].literals, temp, sizeof(int) * count);
            clauses[num_clauses].size = count;
            num_clauses++;
        }
    }

    fclose(file);
    return 1;
}

// Avalia se uma atribuição satisfaz todas as cláusulas
int is_satisfiable(int assignment[]) {
    for (int i = 0; i < num_clauses; i++) {
        int satisfied = 0;
        for (int j = 0; j < clauses[i].size; j++) {
            int lit = clauses[i].literals[j];
            int var = abs(lit);
            int val = assignment[var];

            // Verifica se o literal satisfaz a cláusula
            if ((lit > 0 && val == 1) || (lit < 0 && val == 0)) {
                satisfied = 1;
                break;
            }
        }
        if (!satisfied) return 0; // Uma cláusula não foi satisfeita
    }
    return 1; // Todas as cláusulas foram satisfeitas
}

// SAT Solver por força bruta (tenta todas as combinações)
int solve() {
    int total = 1 << num_vars; // 2^num_vars possibilidades
    int assignment[MAX_VARS + 1]; // assignment[1] até assignment[num_vars]

    for (int i = 0; i < total; i++) {
        // Gera uma atribuição binária
        for (int j = 1; j <= num_vars; j++) {
            assignment[j] = (i >> (j - 1)) & 1;
        }

        if (is_satisfiable(assignment)) {
            printf("SAT\nAssignment:");
            for (int j = 1; j <= num_vars; j++) {
                printf(" %s%d", assignment[j] ? "" : "-", j);
            }
            printf("\n");
            return 1;
        }
    }

    printf("UNSAT\n");
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s arquivo.cnf\n", argv[0]);
        return 1;
    }

    if (!parse_dimacs(argv[1])) {
        fprintf(stderr, "Erro ao analisar o arquivo.\n");
        return 1;
    }

    solve();
    return 0;
}

/**
 * Teste do programa:
 * gcc -o sat_solver.exe sat_index.c -> Cria o executável sat_solver
 * .\sat_solver.exe teste_exemplo.cnf -> Executa o programa com o arquivo teste_exemplo.cnf
 * 
 * O arquivo teste_exemplo.cnf representa a seguinte fórmula:
 * (x1 ∨ ¬x3) ∧ (x2 ∨ x3 ∨ ¬x1)
 * 
 * Essa formula é satisfatível, portanto deverá imprimir algo como:
 * 
 * SAT
 * Assignment: 1 2 3
 * 
 * Equipe: Amós, Dan e Kauê
 */