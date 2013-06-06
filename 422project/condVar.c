/*
 *  condVar.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "condVar.h"
#include "mutex.h"
#include "PCB.h"
#include <stdio.h>
#include <stdlib.h>

CondVarPtr condVarConstruct(MutexPtr mutex, int condition) {
	CondVarPtr temp_condVar = (CondVarPtr) malloc (sizeof(CondVarStr));
	temp_condVar->condition = condition;
	temp_condVar->waiting = Queue_construct();
	temp_condVar->mutex = mutex; 
	return temp_condVar;
}

void CondVar_wait(CondVarPtr condition, PcbPtr pcb) {

	int max = condition->waiting->count;
	int i = 0;
	int alreadyInQueue = 0;

	if (condition == 0)
		return;

	
	// Check to make sure the pcb isn't already in the waiting condition queue.
	for (; i < max; i++) {
		PcbPtr current = Queue_remove(condition->waiting);
		if (current == pcb) {
			alreadyInQueue = 1;
		}
		Queue_add(condition->waiting, current);
	}

	// if not already in queue then add it.
	if (alreadyInQueue == 0) {
		Queue_add(condition->waiting, pcb);
	}

}

void CondVar_signal(CondVarPtr condition) {

	if (condition == 0)
		return;

	// If a signal comes in then take the first pcb off the queue and add it to the conditions mutex waiting queue.
	if (Queue_size(condition->waiting) > 0) {
		// The lock function tries to obtain a lock on the mutex, or puts it in a waiting queue.
		Mutex_lock(condition->mutex, Queue_remove(condition->waiting));
	}


}
