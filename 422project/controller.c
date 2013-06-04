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
	temp_controller->kbQueue = Queue_construct(3);
	temp_controller->hddQueue = Queue_construct(3);
	temp_controller->videoQueue = Queue_construct(3);
	return temp_controller;
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
		printf("P%d is type %d and has service call values", controller->processList[i]->PID, type);
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

void IO_block(ControllerPtr controller, int IODeviceID)
{
	if(IODeviceID == 1) // Send process to Keyboard blocking queue
	{
		Queue_add(controller->kbQueue, controller->runningProcess);
		printf("Process %d was sent to the keyboard blocking queue\n",
				controller->runningProcess->PID);
	}

	else if(IODeviceID == 2) //Send process to hdd blocking queue
	{
		Queue_add(controller->hddQueue, controller->runningProcess);
		printf("Process %d was sent to the hdd blocking queue\n",
				controller->runningProcess->PID);
	}
	else if(IODeviceID == 3) // Send process to video blocking queue
	{
		Queue_add(controller->videoQueue, controller->runningProcess);
		printf("Process %d was sent to the video blocking queue\n",
				controller->runningProcess->PID);
	}

	controller->runningProcess = Queue_remove(controller->readyQueue);
	printf("Process %d is now in the running state\n", controller->runningProcess->PID);
}


