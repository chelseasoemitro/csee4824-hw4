#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_MERGE 32
#define MIN(a, b) ((a) < (b) ? (a) : (b))

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

int intCompare(const void *a, const void *b) {
    uint32_t val_a = *(uint32_t *)a;
    uint32_t val_b = *(uint32_t *)b;

    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

size_t minRunLength(size_t n) {
    size_t r = 0;
    while (n >= MIN_MERGE) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

size_t countRunAndMakeAscending(void *base, size_t len, size_t width, int (*compar)(const void *, const void *)) {
    char *array = (char *)base;
    size_t runLen = 1;
    if (len == 1) return 1;

    if (compar(array + width, array) >= 0) {
        while (runLen < len && compar(array + (runLen * width), array + ((runLen - 1) * width)) >= 0) {
            runLen++;
        }
    } else {
        while (runLen < len && compar(array + (runLen * width), array + ((runLen - 1) * width)) < 0) {
            runLen++;
        }
        for (size_t i = 0, j = runLen - 1; i < j; i++, j--) {
            char temp[width];
            memcpy(temp, array + (i * width), width);
            memcpy(array + (i * width), array + (j * width), width);
            memcpy(array + (j * width), temp, width);
        }
    }
    return runLen;
}

void binarySort(void *base, size_t hi, size_t start, size_t width, int (*compar)(const void *, const void *)) {
    char *array = (char *)base;
    for (size_t i = start; i < hi; i++) {
        char temp[width];
        memcpy(temp, array + (i * width), width);

        size_t left = 0, right = i;
        while (left < right) {
            size_t mid = (left + right) / 2;
            if (compar(temp, array + (mid * width)) < 0) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        memmove(array + ((left + 1) * width), array + (left * width), (i - left) * width);
        memcpy(array + (left * width), temp, width);
    }
}

size_t gallopLeft(void *key, void *base, size_t len, size_t hint, int (*compar)(const void *, const void *), size_t width) {
    char *array = (char *)base;
    size_t lastOfs = 0, ofs = 1;

    if (compar(key, array + hint * width) > 0) {
        size_t maxOfs = len - hint;
        while (ofs < maxOfs && compar(key, array + (hint + ofs) * width) > 0) {
            lastOfs = ofs;
            ofs = (ofs << 1) + 1;
        }
        ofs = MIN(ofs, maxOfs);
        lastOfs += hint;
        ofs += hint;
    } else {
        size_t maxOfs = hint + 1;
        while (ofs < maxOfs && compar(key, array + (hint - ofs) * width) <= 0) {
            lastOfs = ofs;
            ofs = (ofs << 1) + 1;
        }
        ofs = MIN(ofs, maxOfs);
        size_t tmp = lastOfs;
        lastOfs = hint - ofs;
        ofs = hint - tmp;
    }

    while (lastOfs < ofs) {
        size_t mid = lastOfs + (ofs - lastOfs) / 2;
        if (compar(key, array + mid * width) > 0) {
            lastOfs = mid + 1;
        } else {
            ofs = mid;
        }
    }
    return ofs;
}

size_t gallopRight(void *key, void *base, size_t len, size_t hint, int (*compar)(const void *, const void *), size_t width) {
    char *array = (char *)base;
    size_t lastOfs = 0, ofs = 1;

    if (compar(key, array + hint * width) < 0) {
        size_t maxOfs = hint + 1;
        while (ofs < maxOfs && compar(key, array + (hint - ofs) * width) < 0) {
            lastOfs = ofs;
            ofs = (ofs << 1) + 1;
        }
        ofs = MIN(ofs, maxOfs);
        size_t tmp = lastOfs;
        lastOfs = hint - ofs;
        ofs = hint - tmp;
    } else {
        size_t maxOfs = len - hint;
        while (ofs < maxOfs && compar(key, array + (hint + ofs) * width) >= 0) {
            lastOfs = ofs;
            ofs = (ofs << 1) + 1;
        }
        ofs = MIN(ofs, maxOfs);
        lastOfs += hint;
        ofs += hint;
    }

    while (lastOfs < ofs) {
        size_t mid = lastOfs + (ofs - lastOfs) / 2;
        if (compar(key, array + mid * width) < 0) {
            ofs = mid;
        } else {
            lastOfs = mid + 1;
        }
    }
    return ofs;
}

void mergeAt(Timsort *ts, size_t i, size_t width, int (*compar)(const void *, const void *)) {
    Run *run1 = &ts->runStack[i];
    Run *run2 = &ts->runStack[i + 1];

    char *base1 = (char *)run1->base;
    char *base2 = (char *)run2->base;
    size_t len1 = run1->len;
    size_t len2 = run2->len;

    run1->len += len2;
    if (i == ts->stackSize - 3) ts->runStack[i + 1] = ts->runStack[i + 2];
    ts->stackSize--;

    size_t k = gallopRight(base2, base1, len1, 0, compar, width);
    base1 += k * width;
    len1 -= k;
    if (len1 == 0) return;

    len2 = gallopLeft(base1 + (len1 - 1) * width, base2, len2, len2 - 1, compar, width);
    if (len2 == 0) return;

    char *tmp = malloc(len1 * width);
    memcpy(tmp, base1, len1 * width);

    char *cursor1 = tmp;
    char *cursor2 = base2;
    char *dest = base1;

    while (len1 > 0 && len2 > 0) {
        if (compar(cursor1, cursor2) <= 0) {
            memcpy(dest, cursor1, width);
            cursor1 += width;
            len1--;
        } else {
            memcpy(dest, cursor2, width);
            cursor2 += width;
            len2--;
        }
        dest += width;
    }

    if (len1 > 0) memcpy(dest, cursor1, len1 * width);
    if (len2 > 0) memcpy(dest, cursor2, len2 * width);

    free(tmp);
}

void mergeCollapse(Timsort *ts, size_t width, int (*compar)(const void *, const void *)) {
    while (ts->stackSize > 1) {
        size_t n = ts->stackSize - 2;
        if (n > 0 && ts->runStack[n - 1].len <= ts->runStack[n].len + ts->runStack[n + 1].len) {
            if (ts->runStack[n - 1].len < ts->runStack[n + 1].len) n--;
        } else if (ts->runStack[n].len > ts->runStack[n + 1].len) {
            break;
        }
        mergeAt(ts, n, width, compar);
    }
}

void mergeForceCollapse(Timsort *ts, size_t width, int (*compar)(const void *, const void *)) {
    while (ts->stackSize > 1) {
        size_t n = ts->stackSize - 2;
        if (n > 0 && ts->runStack[n - 1].len < ts->runStack[n + 1].len) n--;
        mergeAt(ts, n, width, compar);
    }
}

void timsort(void *base, size_t len, size_t width, int (*compar)(const void *, const void *)) {
    if (len < 2) return;

    size_t minRun = minRunLength(len);
    Timsort ts = {.array = base, .len = len, .minGallop = 7};
    ts.stackCapacity = 16;
    ts.runStack = malloc(ts.stackCapacity * sizeof(Run));

    size_t remaining = len;
    char *array = (char *)base;
    while (remaining) {
        size_t runLen = countRunAndMakeAscending(array, remaining, width, compar);
        if (runLen < minRun) {
            size_t force = MIN(minRun, remaining);
            binarySort(array, force, runLen, width, compar);
            runLen = force;
        }
        ts.runStack[ts.stackSize++] = (Run){.base = array, .len = runLen};
        mergeCollapse(&ts, width, compar);

        array += runLen * width;
        remaining -= runLen;
    }
    mergeForceCollapse(&ts, width, compar);

    free(ts.runStack);
}

uint32_t *tim_sort(uint32_t *arr, size_t size) {
    timsort(arr, size, sizeof(uint32_t), intCompare);

    return arr;
}
