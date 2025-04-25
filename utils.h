#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Função de contagem usada pelo compressor.
 * 
 * Conta a frequência de cada byte em um arquivo (Ex: freq[A] = 4, freq[B] = 3, etc.).
 * 
 * @param file Ponteiro para o arquivo aberto em modo binário.
 * @param freq Array de 256 inteiros onde as frequências serão armazenadas.
 */
void count_frequencies(FILE* file, int freq[256]);

/**
 * @brief Função de comparação usada pela Min Heap.
 * 
 * Compara dois nós Huffman pela frequência.
 * 
 * @param a Ponteiro genérico para HuffmanNode.
 * @param b Ponteiro genérico para HuffmanNode.
 * @return Negativo se a < b, positivo se a > b, zero se iguais.
 */
int compare_freq(void* a, void* b);

#endif
