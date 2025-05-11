#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include "compress.h"
#include "decompress.h"
#include <unistd.h>

#define MAX_FILENAME 256
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// Arte ASCII do nome HUFFMAN
void print_ascii_art() {
    printf(COLOR_CYAN "\n");
    printf("██   ██ ██    ██ ███████ ███████ ███    ███  █████  ███    ██ \n");
    printf("██   ██ ██    ██ ██      ██      ████  ████ ██   ██ ████   ██ \n");
    printf("███████ ██    ██ █████   █████   ██ ████ ██ ███████ ██ ██  ██ \n");
    printf("██   ██ ██    ██ ██      ██      ██  ██  ██ ██   ██ ██  ██ ██ \n");
    printf("██   ██  ██████  ██      ██      ██      ██ ██   ██ ██   ████ \n");
    printf(COLOR_RESET "\n\n");
}

// Verifica se é arquivo .huff
bool is_huff_file(const char* filename) {
    const char* dot = strrchr(filename, '.');
    return dot && !strcmp(dot, ".huff");
}

// Remove extensão do arquivo
void remove_extension(char* filename) {
    char* dot = strrchr(filename, '.');
    if (dot) *dot = '\0';
}

// Obtém o tamanho do arquivo em bytes
long get_file_size(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == 0)
        return st.st_size;
    return -1;
}

// Mostra barra de progresso simples
void show_progress(float progress) {
    int width = 50;
    printf(COLOR_BLUE "[");
    int pos = width * progress;
    for (int i = 0; i < width; i++) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %d%%\r" COLOR_RESET, (int)(progress * 100));
    fflush(stdout);
}

const char* get_original_extension(const char* filename) {
    const char* huff_ext = strstr(filename, ".huff");
    if (!huff_ext) return NULL;
    
    // Encontra o último ponto antes do .huff
    const char* last_dot = filename;
    for (const char* p = filename; p < huff_ext; p++) {
        if (*p == '.') last_dot = p;
    }
    
    // Se encontrou um ponto e não é o primeiro caractere
    if (last_dot != filename && last_dot < huff_ext) {
        return last_dot;
    }
    return NULL;
}

// Gera nome do arquivo de saída com o formato especificado
void get_output_filename(const char* input, char* output, bool is_huff) {
    strncpy(output, input, MAX_FILENAME);
    output[MAX_FILENAME - 1] = '\0'; // Garante terminação
    
    if (is_huff) {
        // Remove .huff primeiro
        char* huff_ext = strstr(output, ".huff");
        if (huff_ext) *huff_ext = '\0';
        
        // Verifica se há extensão original
        const char* orig_ext = get_original_extension(input);
        if (orig_ext) {
            // Se encontrou extensão original, mantém até o .huff
        } else {
            // Sem extensão original - adiciona .dec
            strncat(output, ".dec", MAX_FILENAME - strlen(output) - 1);
        }
    } else {
        // Compactando: adiciona .huff mantendo a extensão original
        strncat(output, ".huff", MAX_FILENAME - strlen(output) - 1);
    }
}

// Mostra informações sobre a operação
void show_operation_info(const char* input, const char* output, bool is_huff, 
                        double time_taken, long original_size, long new_size) {
    printf("\n\n" COLOR_GREEN "=== Informações da Operação ===" COLOR_RESET "\n");
    printf("Arquivo de entrada:  %s\n", input);
    printf("Arquivo de saída:    %s\n", output);
    printf("Tipo de operação:   %s\n", is_huff ? "Descompressão" : "Compressão");
    printf("Tempo decorrido:    %.2f segundos\n", time_taken);
    
    if (original_size > 0 && new_size > 0) {
        printf("Tamanho original:   %ld bytes\n", original_size);
        printf("Tamanho final:      %ld bytes\n", new_size);
        
        if (!is_huff) {
            float ratio = (1 - (float)new_size / original_size) * 100;
            printf("Taxa de compressão: %.2f%%\n", ratio);
        }
    }
    
    printf(COLOR_GREEN "Operação concluída com sucesso!" COLOR_RESET "\n\n");
}

int main() {
    char input_filename[MAX_FILENAME];
    char output_filename[MAX_FILENAME];
    char choice;
    clock_t start, end;
    double time_taken;
    long original_size, new_size;
    
    do {
        print_ascii_art();
        printf(COLOR_YELLOW "=== Huffman File Processor ===\n" COLOR_RESET);
        printf(COLOR_MAGENTA "Digite o nome do arquivo (ou 's' para sair): " COLOR_RESET);
        
        if (fgets(input_filename, MAX_FILENAME, stdin) == NULL) {
            printf(COLOR_RED "Erro ao ler nome do arquivo.\n" COLOR_RESET);
            return 1;
        }
        
        // Remove newline do final
        input_filename[strcspn(input_filename, "\n")] = '\0';
        
        // Verifica se o usuário quer sair
        if (strcmp(input_filename, "s") == 0 || strcmp(input_filename, "S") == 0) {
            break;
        }
        
        // Verifica se arquivo existe
        FILE* test = fopen(input_filename, "rb");
        if (!test) {
            printf(COLOR_RED "\nArquivo não encontrado!\n" COLOR_RESET);
            printf("Pressione Enter para continuar...");
            getchar();
            continue;
        }
        fclose(test);
        
        bool is_huff = is_huff_file(input_filename);
        get_output_filename(input_filename, output_filename, is_huff);
        
        // Obtém tamanho original do arquivo
        original_size = get_file_size(input_filename);
        
        printf("\n" COLOR_CYAN "Processando arquivo: %s\n" COLOR_RESET, input_filename);
        printf(COLOR_CYAN "Arquivo de saída:    %s\n\n" COLOR_RESET, output_filename);
        
        // Simula barra de progresso
        for (int i = 0; i <= 10; i++) {
            show_progress(i/10.0);
            usleep(100000); // 100ms delay
        }
        
        // Executa a operação
        start = clock();
        
        if (is_huff) {
            decompress_file(input_filename, output_filename);
        } else {
            compress_file(input_filename, output_filename);
        }
        
        end = clock();
        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Obtém tamanho do novo arquivo
        new_size = get_file_size(output_filename);
        
        // Mostra informações detalhadas
        show_operation_info(input_filename, output_filename, is_huff, 
                          time_taken, original_size, new_size);
        
        printf("Deseja processar outro arquivo? (s/n): ");
        choice = getchar();
        while (getchar() != '\n'); // Limpa buffer
        
    } while (choice == 's' || choice == 'S');
    
    printf(COLOR_YELLOW "\nObrigado por usar o Huffman File Processor!\n" COLOR_RESET);
    printf(COLOR_YELLOW "Até a próxima!\n\n" COLOR_RESET);
    
    return 0;
}