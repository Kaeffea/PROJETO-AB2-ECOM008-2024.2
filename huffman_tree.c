#include <stdlib.h>
#include "structs.h"

/**
 * @brief Cria um novo nó da árvore de Huffman.
 * 
 * @param byte Ponteiro para o byte representado (NULL para nós internos)
 * @param freq Ponteiro para a frequência (int*)
 * @param left Filho esquerdo (HuffmanNode*)
 * @param right Filho direito (HuffmandNode*)
 * @return Ponteiro para o novo HuffmanNode
 */
HuffmanNode* create_node(void* byte, void* freq, void* left, void* right){
    HuffmanNode* node = malloc(sizeof(HuffmanNode));
    node->byte = byte;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}