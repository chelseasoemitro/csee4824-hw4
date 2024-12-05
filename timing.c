#include "timing.h"

inline void mfence() {
    asm volatile ("mfence" ::: "memory");
}

static inline int64_t time_start(void) {
    uint64_t a, d;
    asm volatile("cpuid" ::: "%rax", "%rbx", "%rcx", "%rdx");
    asm volatile("rdtsc" : "=a" (a), "=d" (d));
    return ((uint64_t)a) | (((uint64_t)d) << 32);
}

static inline int64_t time_stop(void) {
    uint64_t a, d;
    asm volatile("rdtscp" : "=a" (a), "=d" (d));
    asm volatile("cpuid" ::: "%rax", "%rbx", "%rcx", "%rdx");
    return ((uint64_t)a) | (((uint64_t)d) << 32);
