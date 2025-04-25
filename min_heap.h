#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "structs.h"

/**
 * @brief Tipo de função para comparar dois elementos genéricos.
 * Deve retornar negativo se a < b, 0 se a == b, positivo se a > b.
 */
typedef int (*CompareFunc)(void* a, void* b);

#endif