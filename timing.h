#ifndef TIMING_H
#define TIMING_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t time_start(void);
uint64_t time_stop(void);

#ifdef __cplusplus
}
#endif

#endif // TIMING_H