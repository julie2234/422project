/*
 *  mutex.h
 *	GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef MUTEX_H
#define MUTEX_H

#include "queue.h"

typedef struct mutex_str {
	int owner;
	struct queue_str waitingQueue;
} MutexStr;

typedef MutexStr* MutexPtr;

MutexPtr mutexConstruct();
void Mutex_lock(MutexPtr mutex, PcbPtr pcb);
void Mutex_unlock(MutexPtr mutex, PcbPtr pcb);

#endif

