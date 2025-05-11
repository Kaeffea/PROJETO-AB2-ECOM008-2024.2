#ifndef METRICS_H
#define METRICS_H

#include "structs.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

extern int comparison_counter;

// Zera o contador
void reset_comparisons();

// Incrementa o contador
void increment_comparisons();

// Retorna o valor atual do contador
int get_comparisons();

#endif
