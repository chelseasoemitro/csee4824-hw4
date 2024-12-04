#ifndef TIMSORT_H
#define TIMSORT_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    void *base;
    size_t len;
} Run;

typedef struct {
    void *array;
    size_t len;
    size_t minGallop;
    Run *runStack;
    size_t stackSize;
    size_t stackCapacity;
} Timsort;

void timsort(void *base, size_t len, size_t width, int (*compar)(const void *, const void *));
int intCompare(const void *a, const void *b);

#endif // TIMSORT_H
