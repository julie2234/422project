/*
 *  controller.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "controller.h"
#include "CPU.h"

ControllerPtr controllerConstruct() {
	ControllerPtr temp_controller = (ControllerPtr) malloc (sizeof(ControllerStr));
	temp_controller->readyQueue = Queue_construct(5);
	return temp_controller;
}

//This function was just a test to see if functions could be called from within a threaded
//function. It will be replaced when we decide how the timer will interact with the
//controller.
void timeEndInterrupt()
{
	printf("Time ended!\n");
}

int main ()
{
	ControllerPtr controller = controllerConstruct();
	
	//just for testing
	controller->processList[0] = pcbConstruct(0, 1);
	controller->processList[1] = pcbConstruct(1, 3);
	controller->processList[2] = pcbConstruct(2, 2);
	controller->processList[3] = pcbConstruct(3, 4);
	
	printf("Process Summary\n");
	int i;
	for (i = 0; i < 4; i++)
	{
		int type = controller->processList[i]->processType;
		printf("P%d is type %d and has service call values", i, type);
		int j;
		for (j = 0; j < 8; j++) {
			printf(" %d", controller->processList[i]->serviceCallValues[j]);
		}
		printf("\n");
		Queue_add(controller->readyQueue, controller->processList[i]);
	}
	controller->runningProcess = Queue_remove(controller->readyQueue);
	printf("\nP%d is running \n", controller->runningProcess->PID);

	startTimer(5);
	//scheduler(controller);

	CpuPtr cpu = cpuConstruct(controller);
	cpuRun(cpu);

	pthread_exit(NULL);
}


void scheduler(ControllerPtr this) {
	Queue_add(this->readyQueue, this->runningProcess);
	PcbPtr process = Queue_remove(this->readyQueue); 
	printf("\nP%d is running \n", process->PID);
	process->state = RUNNING; // change the state in its PCB to RUNNING
	this->runningProcess = process; 
}


