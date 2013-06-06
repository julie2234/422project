#include "prod_cons.h"
#include "CPU.h"
#include "mutex.h"
#include <stdio.h>

// Global "shared" memory.
int mem;
// Global condition variable.
int new_mem;
// Shared memory mutex.
struct mutex_str mem_mut;

int get_mutex_process() {
	return mem_mut.owner;
}

void Consumer_tick(CpuPtr cpu) {

	PcbPtr current = cpu->controller->runningProcess;

	//printf("ConsumerTick_currentCount[%d]...\n", current->currentCount);

	// Calculate the consumer stage. (General Contract here is that the next stage cannot be reached without the previous succeeding.)
	// Stage 1 - Attempt to retrieve the mutex. (instant -> does not have anything to do with current count)
	if (mem_mut.owner == 0 && new_mem == 1) {

		mem_mut.owner = current->PID;
		//printf("Consumer has recieved the mutex lock\n");

	// Stage 2 - Attempt to write to vid.
	} else if (mem_mut.owner == current->PID && current->currentCount <= (current->count / 2)) {

		current->currentCount++;

		if (current->currentCount == 1)
			printf("------------------------------\nConsumer[P%d] Output -> %d\n------------------------------\n", current->PID, mem);


	// Stage 3 - Unlock the mutex.		
	} else if (current->currentCount > (current->count / 2) && current->currentCount < current->count) {

		// If the lock is still owned by me-unlock it and increment.
		// If not then just waste time and restart.
		if (mem_mut.owner == current->PID) {
			mem_mut.owner = 0;
			new_mem = 0;
		} /* else { implied do nothing but waste time. } */

		current->currentCount = (current->currentCount + 1) % current->count;

		//printf("Consumer has passed back the lock\n");

	} else { 
		//printf("Consumer waiting for data...\n");
	}

}

void Producer_tick(CpuPtr cpu) {

	PcbPtr current = cpu->controller->runningProcess;

	// Calculate the producer stage. (General Contract here is that the next stage cannot be reached without the previous succeeding.)
	//printf("ProducerTick_currentCount[%d/%d]...\n", current->currentCount, current->count);
	// Stage 1 - Do nothing here but increase count (for the number display).
	if (current->currentCount <= (current->count / 4)) { 
		
		//printf("Producer wasting time [%d/%d]...\n", current->currentCount, current->count);
		current->currentCount++;

	// Stage 2 - Try and obtain a lock to the mutex.
	} if (current->currentCount <= (current->count / 2) && current->currentCount > (current->count / 4)) {
	
		// Check to see if the mutex is owned by me AND if there is NOT new mem still in memory.
			// If it is then just waste time but count up.
			// If it is NOT and NOT null then waste time.
			// If it is NOT owned by anyone then get it and count up.
		if (mem_mut.owner == current->PID && new_mem == 0) {
			current->currentCount++;
			//printf("Producer waiting to retrieve mutex...\n");
		} else if (mem_mut.owner == 0 && new_mem == 0) {
			mem_mut.owner = current->PID;
			current->currentCount++;
			//printf("Producer has received mutex lock\n");
		} else { 
			//printf("Producer busy waiting...\n");
		}

	// Stage 3 - Save the data (PID or something) to the shared bit of memory.
	} else if (current->currentCount <= (3*current->count / 4) && current->currentCount > (current->count / 2)) {

		mem = current->PID;
		new_mem = 1;
		current->currentCount++;
		//printf("Producer has written data\n");


	// Stage 4 - Release the mutex and restart.
	} else if (current->currentCount <= current->count && current->currentCount > (3*current->count / 4)) {

		// Check to see if the mutex is owned by me.
			// If it is then unlock it.
			// If it is not (or not owned at all) just keep counting... wasting time.
		if (mem_mut.owner == current->PID) {
			mem_mut.owner = 0;
			//printf("Producer has unlocked mutex\n");
		} else {
			//printf("Producer is busy waiting...");
		}
		
		current->currentCount = (current->currentCount + 1) % current->count;

	}
	
}
