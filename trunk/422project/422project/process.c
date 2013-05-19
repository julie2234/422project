/*
 *  process.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
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

void run(ProcessPtr this) {
	switch(this->processType) {
		case(KEYBOARD):
			printf("ran keyboard process");
			break;
		case(COMPUTE):
			printf("ran compute process");
			break;
		case(IO):
			printf("ran io process");
			break;
		case(PRODUCER):
			printf("ran producer process");
			break;
		case(CONSUMER):
			printf("ran consumer process");
			break;
	}
}

