/*
 *  condVar.h
 *	GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef CONDVAR_H
#define CONDVAR_H

#include "mutex.h"
#include "queue.h"

#define C1 1 // new mem condition
#define C2 2 // no mem condition

typedef struct condVar_str {
	int condition;
	QueuePtr waiting;
	MutexPtr mutex;
} CondVarStr;

typedef CondVarStr* CondVarPtr;

CondVarPtr condVarConstruct(MutexPtr mutex, int condition);
void CondVar_wait(CondVarPtr condition, PcbPtr pcb);
void CondVar_signal(CondVarPtr condition);

#endif
