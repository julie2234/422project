/*
 *  controller.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "controller.h"
#include <stdio.h>
#include <stdlib.h>

ControllerPtr controllerConstruct() {
	ControllerPtr temp_controller = (ControllerPtr) malloc (sizeof(ControllerStr));
	return temp_controller;
}

int main () {
	ControllerPtr controller = controllerConstruct();
	
	//just for testing
	controller->processList[0] = pcbConstruct(0, 1);
	controller->processList[1] = pcbConstruct(1, 3);
	
	printf("Process Summary\n");
	int i;
	for (i = 0; i < 2; i++) {
		int type = controller->processList[i]->processType;
		printf("P%d is of type %d\n", i, type);
	}
	scheduler(controller);
}


void scheduler(ControllerPtr this) {
	//PcbPtr process = readyQueue.dequeue(); // dequeue a process from the ready queue 
	//process->state = RUNNING; // change the state in its PCB to RUNNING
	//run(process); // call the run method in process.c
	//this->runningProcess = process; 
}


