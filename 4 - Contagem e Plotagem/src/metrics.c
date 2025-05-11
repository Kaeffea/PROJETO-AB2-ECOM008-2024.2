#include "structs.h"
#include "priority_list_unsorted.h"
#include "priority_heap.h"
#include "metrics.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int comparison_counter = 0;

void reset_comparisons() {
    comparison_counter = 0;
}

void increment_comparisons() {
    comparison_counter++;
}

int get_comparisons() {
    return comparison_counter;
}