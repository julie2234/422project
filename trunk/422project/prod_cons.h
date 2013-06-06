#ifndef PROD_CONS_H
#define PROD_CONS_H

#include "CPU.h"
#include "mutex.h"

// Global "shared" memory.
int mem;
// Global condition variable.
int new_mem;
// Shared memory mutex.
struct mutex_str mem_mut;

// nothing
void Producer_tick(CpuPtr);
void Consumer_tick(CpuPtr);

#endif