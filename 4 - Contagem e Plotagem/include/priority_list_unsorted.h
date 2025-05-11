#ifndef PRIORITY_LIST_UNSORTED_H
#define PRIORITY_LIST_UNSORTED_H

#include "structs.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void init_list(PriorityList* lista);

void insert_unsorted(PriorityList* lista, void* dados, int prioridade);

PriorityItem* remove_min_unsorted(PriorityList* lista);

void free_list(PriorityList* lista, void (*free_data)(void*));

#endif