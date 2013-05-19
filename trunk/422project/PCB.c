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


