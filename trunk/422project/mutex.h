/*
 *  mutex.h
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef MUTEX_H
#define MUTEX_H

typedef struct mutex_str {
	int owner;
	//queue waitingQueue;
} MutexStr;

typedef MutexStr* MutexPtr;

#endif

