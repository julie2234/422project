/*
 *  process.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "process.h"
#include <stdio.h>
#include <stdlib.h>

ProcessPtr processContruct(int the_processType, int the_PID) {
	ProcessPtr temp_process = (ProcessPtr) malloc(sizeof(ProcessStr));
	temp_process->processType = the_processType;
	return temp_process;
}



