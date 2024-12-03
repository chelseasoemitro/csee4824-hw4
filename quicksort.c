#include <stdlib.h>
#include "sorting.h"

static int compare_ints(const void *a, const void *b) {
    int *a_int = (int *)a;
    int *b_int = (int *)b;
    return *a_int - *b_int;
}

uint32_t *quick_sort(uint32_t *arr, size_t size) {
    qsort(arr, size, sizeof(*arr), compare_ints);
    return arr;
}
