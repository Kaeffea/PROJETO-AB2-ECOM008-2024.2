#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#include "structs.h"

void count_frequencies(FILE* file, int freq[256]){
    unsigned char byte;
    while (fread(&byte, sizeof(unsigned char), 1, file)){ // Lê 1 byte por vez do arquivo e armazena em 'byte'
        freq[byte]++; // Incrementa a frequência do byte no vetor 'freq'
    }
    rewind(file); // Volta ao início do arquivo para reutilização
}

int compare_freq(void* a, void* b){
    // Tipa os nós de Huffman
    HuffmanNode* nodeA = (HuffmanNode*) a;
    HuffmanNode* nodeB = (HuffmanNode*) b;
    // Tipa como inteiro as frequências dos nós
    int freqA = *(int*)nodeA->freq;
    int freqB = *(int*)nodeB->freq;
    // Retorna o valor de comparação entre duas frequências
    return freqA - freqB;
}

