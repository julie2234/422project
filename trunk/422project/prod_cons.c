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

void Consumer_tick(CpuPtr cpu) {

	// Calculate the consumer stage. (General Contract here is that the next stage cannot be reached without the previous succeeding.)
	// Stage 1 - Attempt to retrieve the mutex. (instant -> does not have anything to do with current count)
	if (mem_mut.owner == 0 && new_mem == 1) {

		mem_mut.owner = cpu->current_pcb->PID;

	// Stage 2 - Attempt to write to vid.
	} else if (mem_mut.owner == cpu->current_pcb->PID && cpu->current_pcb->currentCount <= (cpu->current_pcb->count / 2)) {

		cpu->current_pcb->currentCount++;

		if (cpu->current_pcb->currentCount == 1)
			sprintf("Consumer[%d] Output -> %d", cpu->current_pcb->PID, mem);


	// Stage 3 - Unlock the mutex.		
	} else if (cpu->current_pcb->currentCount > (cpu->current_pcb->count / 2) && cpu->current_pcb->currentCount < cpu->current_pcb->count) {

		// If the lock is still owned by me-unlock it and increment.
		// If not then just waste time and restart.
		if (mem_mut.owner == cpu->current_pcb->PID) {
			mem_mut.owner = 0;
			new_mem = 0;
		} /* else { implied do nothing but waste time. } */

		cpu->current_pcb->currentCount = (cpu->current_pcb->currentCount + 1) % cpu->current_pcb->count;

	} /* else { implied do nothing } */

}

void Producer_tick(CpuPtr cpu) {

	// Calculate the producer stage. (General Contract here is that the next stage cannot be reached without the previous succeeding.)
	
	// Stage 1 - Do nothing here but increase count (for the number display).
	/* if (cpu->current_pcb->currentCount <= (cpu->current_pcb->count / 4)) { 
		
		implied waste time doing nothing... */

	// Stage 2 - Try and obtain a lock to the mutex.
	if (cpu->current_pcb->currentCount <= (cpu->current_pcb->count / 2) && cpu->current_pcb->currentCount > (cpu->current_pcb->count / 4)) {
	
		// Check to see if the mutex is owned by me AND if there is NOT new mem still in memory.
			// If it is then just waste time but count up.
			// If it is NOT and NOT null then waste time.
			// If it is NOT owned by anyone then get it and count up.
		if (mem_mut.owner == cpu->current_pcb->PID && new_mem == 0) {
			cpu->current_pcb->currentCount++;
		} else if (mem_mut.owner == 0 && new_mem == 0) {
			mem_mut.owner = cpu->current_pcb->PID;
			cpu->current_pcb->currentCount++;
		} /* else { implied do nothing if owned by another. } */

	// Stage 3 - Save the data (PID or something) to the shared bit of memory.
	} else if (cpu->current_pcb->currentCount <= (3*cpu->current_pcb->count / 4) && cpu->current_pcb->currentCount > (cpu->current_pcb->count / 2)) {

		mem = cpu->current_pcb->PID;
		new_mem = 1;

	// Stage 4 - Release the mutex and restart.
	} else if (cpu->current_pcb->currentCount <= cpu->current_pcb->count && cpu->current_pcb->currentCount > (3*cpu->current_pcb->count / 3)) {

		// Check to see if the mutex is owned by me.
			// If it is then unlock it.
			// If it is not (or not owned at all) just keep counting... wasting time.
		if (mem_mut.owner == cpu->current_pcb->PID) {
			mem_mut.owner = 0; 
		} /* else { implied do nothing... } */
		
		cpu->current_pcb->currentCount = (cpu->current_pcb->currentCount + 1) % cpu->current_pcb->count;

	}
	
}
