/*
 *  mutex.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "mutex.h"
#include "PCB.h"
#include <stdio.h>
#include <stdlib.h>

MutexPtr mutexConstruct() {
	MutexPtr temp_mutex = (MutexPtr) malloc (sizeof(MutexStr));
	return temp_mutex;
}

void Mutex_lock(MutexPtr mutex, PcbPtr pcb) {

	if (mutex == 0)
		return;

	// If someone currently owns the lock place them in the queue.
	if (mutex->owner != 0) {
		Queue_add(&mutex->waitingQueue, pcb);
	// If no one owns it then it's all yours...
	} else {
		mutex->owner = pcb->PID;
	}
}

void Mutex_unlock(MutexPtr mutex, PcbPtr pcb) {

	// Do nothing if the mutex or pcb are null, and if another pcb tries to unlock someone elses mutex.
	if (mutex == 0 || pcb == 0 || mutex->owner != pcb->PID)
		return;

	// Just switch the pcb from the queue (if any) to the owner position.
	mutex->owner = 0;
	if (Queue_size(&mutex->waitingQueue) > 0) {
		mutex->owner = Queue_remove(&mutex->waitingQueue)->PID;
	}

}
