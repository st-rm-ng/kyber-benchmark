#ifndef CPUCYCLES_H
#define CPUCYCLES_H

#include <stdint.h>
#include <time.h>

static inline uint64_t cpucycles(void) {
    struct timespec ts;
    uint64_t cycles;

    // Get the current time using a high-resolution clock
    clock_gettime(CLOCK_MONOTONIC, &ts);

    // Convert the time to cycles
    cycles = (uint64_t)ts.tv_sec * 1000000000 + ts.tv_nsec;

    return cycles;
}

uint64_t cpucycles_overhead(void);

#endif
