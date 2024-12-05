#ifndef TIMING_H
#define TIMING_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int64_t time_start(void);
int64_t time_stop(void);

#ifdef __cplusplus
}
#endif

#endif // TIMING_H