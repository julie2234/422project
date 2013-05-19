/*
 *  PCB.h
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef PCB_H
#define PCB_H
#include "process.h"

// States
#define RUNNING		0
#define READY		1
#define INTERRUPTED	2
#define BLOCKED		3

typedef struct pcb_str {
	int PID;
	int processType;
	ProcessPtr process;
	int state;
	int count;
	int currentCount;
	int serviceCallValues[4];
	int waiting_on;		// which queue is it in if it is waiting on something (blocked)
	int owns;			// which mutex lock does it own
						// anything else you need
} PcbStr;

typedef PcbStr* PcbPtr;

#endif
