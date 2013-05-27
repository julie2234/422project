/*
 *  PCB.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "PCB.h"
#include <stdio.h>
#include <stdlib.h>

PcbPtr pcbConstruct(int the_PID, int the_processType) {
	PcbPtr temp_pcb = (PcbPtr) malloc(sizeof(PcbStr));
	temp_pcb->PID = the_PID;
	temp_pcb->processType = the_processType;
	temp_pcb->process = processContruct(the_processType);
	temp_pcb->state = READY;
	//temp_pcb->count =	// initialize count to a random number
	temp_pcb->currentCount = 0;
	int i;
	for (i = 0; i < sizeof(temp_pcb->serviceCallValues); i++) {
		// initialize serviceCallValues[] array to random numbers between 0 and count
	}
	return temp_pcb;
}

/************************************************************
* This code is added for processing data after the DeviceIO *
* has initialized the PCB and has gone through the ready    *
* queue and is ready to be processed.                       *
* This method is called by the CPU until the data has been  *
* fully processed, or until an interupt occurse.            *
* By using this method the thread running in the PCB does   *
* not get interupted but the CPU its self is interupted     *
************************************************************/

int pcbIterator() {
    int boolean = temp_pcb->count - temp_pcb->currentCount;
    if (boolean > 0) {
       temp_pcb->clock_counter++;  
       // Input code hear if you wish to process something.
       // Currently just iterates through the data and does nothing.                        
    }
    return boolean; //returns true if the PCB is not completely processed.
}


