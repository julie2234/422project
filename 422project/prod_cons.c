#include "prod_cons.h"
#include "condVar.h"
#include "CPU.h"
#include "mutex.h"
#include <stdio.h>

int first_run = 1;

void setupConditions() {
	mem_mut = mutexConstruct();
	cond_new_mem = condVarConstruct(mem_mut, C1);
	cond_no_mem = condVarConstruct(mem_mut, C2);
	// Initially signal for no mem.
	CondVar_signal(cond_no_mem);
}

void destructConditions() {
	if (cond_new_mem != 0) {
		free(cond_new_mem);
		cond_new_mem = 0;
	}
	if (cond_no_mem != 0) {
		free(cond_no_mem);
		cond_no_mem = 0;
	}
	if (mem_mut != 0) {
		free(mem_mut);
		mem_mut = 0;
	}
}

void Consumer_tick(CpuPtr cpu) {

	PcbPtr current = cpu->controller->runningProcess;

	printf("----------------------------------------\nConsumerTick_currentCount[%d/%d]...\n", current->currentCount, current->count);

	// If the consumer does not have the mutex then attempt to get it.
	if (mem_mut->owner != current->PID) {
		CondVar_wait(cond_new_mem, current);
	}

	
	// If the consumer has the mutex pointer then display that it has retrieved it.
	if (mem_mut->owner == current->PID && current->currentCount == 0) {
		printf("Consumer has recieved the mutex lock\n");
		current->currentCount++;
	} else if (mem_mut->owner == current->PID && current->currentCount <= (current->count / 2)) {

		// Write to vid.
		current->currentCount++;

		if (current->currentCount == 1)
			printf("Consumer[%d] Output -> %d\n", current->PID, mem);

	} else if (mem_mut->owner == current->PID && current->currentCount > (current->count / 2)) {

		CondVar_signal(cond_no_mem);
		Mutex_unlock(mem_mut, current);
		//mem_mut.owner = 0;
		//new_mem = 0;
		current->currentCount = 0;
		printf("Consumer has passed back the lock and signaled no data\n");

	} else {

		printf("Consumer is waiting for new mem condition...\n");

	}
	
	printf("----------------------------------------\n");

	/*
	// Calculate the consumer stage. (General Contract here is that the next stage cannot be reached without the previous succeeding.)
	// Stage 1 - Attempt to retrieve the mutex. (instant -> does not have anything to do with current count)
	if (mem_mut.owner == 0 && new_mem == 1) {

		mem_mut.owner = current->PID;
		printf("Consumer has recieved the mutex lock\n");

	// Stage 2 - Attempt to write to vid.
	} else if (mem_mut.owner == current->PID && current->currentCount <= (current->count / 2)) {

		current->currentCount++;

		if (current->currentCount == 1)
			printf("Consumer[%d] Output -> %d\n", current->PID, mem);


	// Stage 3 - Unlock the mutex.		
	} else if (current->currentCount > (current->count / 2) && current->currentCount < current->count) {

		// If the lock is still owned by me-unlock it and increment.
		// If not then just waste time and restart.
		if (mem_mut.owner == current->PID) {
			mem_mut.owner = 0;
			new_mem = 0;
			current->currentCount = 0;
			printf("Consumer has passed back the lock\n");
		}
		
	} else { 
		printf("Consumer waiting for data...\n");
	}

	printf("----------------------------------------\n");
	*/
}

void Producer_tick(CpuPtr cpu) {

	PcbPtr current = cpu->controller->runningProcess;

	printf("----------------------------------------\nProducerTick_currentCount[%d/%d]...\n", current->currentCount, current->count);

	// If the producer does not have the mutex then attempt to get it.
	if (first_run == 1) {
		// Obtain the mutex lock on first run to seed the program.
		Mutex_lock(mem_mut, current);
		first_run = 0;
	} else if (mem_mut->owner != current->PID) {
		CondVar_wait(cond_no_mem, current);
	}
	
	if (mem_mut->owner == current->PID && current->currentCount == 0) {

		printf("Producer retrieved mutex.\n");
		current->currentCount++;

	} else if (mem_mut->owner == current->PID && current->currentCount == 1) {

		if (current->currentCount == 1) {
			printf("Producer writing data...\n");
			mem = current->PID;
		} else {
			printf("Producer wasting time after data writing...\n");
		}

		current->currentCount++;

	} else if (mem_mut->owner == current->PID && current->currentCount == 2) {

		printf("Producer unlocking mutex and signalling new data...\n");
		CondVar_signal(cond_new_mem);
		Mutex_unlock(mem_mut, current);

		current->currentCount = 0;

	} else {

		printf("Producer waiting for no data condition...\n");

	}
	
	printf("----------------------------------------\n");
	
	
	/*

	// Calculate the producer stage. (General Contract here is that the next stage cannot be reached without the previous succeeding.)
	printf("----------------------------------------\nProducerTick_currentCount[%d/%d]...\n", current->currentCount, current->count);
	// Stage 1 - Do nothing here but increase count (for the number display).
	if (current->currentCount <= (current->count / 4)) { 
		
		printf("Producer wasting time to retrieve mutex...\n", current->currentCount, current->count);
		current->currentCount++;

	// Stage 2 - Try and obtain a lock to the mutex.
	} else if (current->currentCount <= (current->count / 2) && current->currentCount > (current->count / 4)) {
	
		// Check to see if the mutex is owned by me AND if there is NOT new mem still in memory.
			// If it is then just waste time but count up.
			// If it is NOT and NOT null then waste time.
			// If it is NOT owned by anyone then get it and count up.
		if (mem_mut.owner == current->PID && new_mem == 0) {
			current->currentCount++;
			printf("Producer waiting to write data (has mutex)...\n");
		} else if (mem_mut.owner == 0 && new_mem == 0) {
			mem_mut.owner = current->PID;
			current->currentCount++;
			printf("Producer has received mutex lock\n");
		} else { 
			printf("Producer busy waiting to retrieve mutex lock...\n");
		}

	// Stage 3 - Save the data (PID or something) to the shared bit of memory.
	} else if (current->currentCount <= (3*current->count / 4) && current->currentCount > (current->count / 2)) {

		mem = current->PID;
		new_mem = 1;
		current->currentCount++;
		printf("Producer has written data\n");


	// Stage 4 - Release the mutex and restart.
	} else if (current->currentCount <= current->count && current->currentCount > (3*current->count / 4)) {

		// Check to see if the mutex is owned by me.
			// If it is then unlock it.
			// If it is not (or not owned at all) just keep counting... wasting time.
		if (mem_mut.owner == current->PID) {
			mem_mut.owner = 0;
			printf("Producer has unlocked mutex\n");
		} else {
			printf("Producer busy waiting to start over...\n");
		}
		
		current->currentCount = (current->currentCount + 1) % current->count;

	}

	printf("----------------------------------------\n");
	*/
}
