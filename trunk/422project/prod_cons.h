/*
 *  prod_cons.h
 *  GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef PROD_CONS_H
#define PROD_CONS_H

#include "CPU.h"
#include "mutex.h"
#include "condVar.h"

// Global "shared" memory.
int mem;
// Global condition variable.
//int new_mem;
// Shared memory mutex.
//struct mutex_str mem_mut;

MutexPtr mem_mut;
CondVarPtr cond_new_mem;
CondVarPtr cond_no_mem;

// nothing
void Producer_tick(CpuPtr);
void Consumer_tick(CpuPtr);
void setupConditions();
void destructConditions();

#endif
