/*
 *  controller.h
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "PCB.h"
#include "process.h"

typedef struct controller_str {
	PcbPtr processList[2];
	//PcbPtr readyQueue //this will be a queue
	ProcessPtr runningProcess;
	ProcessPtr interruptedProcess;
} ControllerStr;

typedef ControllerStr* ControllerPtr;

#endif

