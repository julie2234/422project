/*
 *  controller.c
 *      GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *      TCSS 422, Spring 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "controller.h"
#include "CPU.h"

ControllerPtr controllerConstruct() {
	ControllerPtr temp_controller = (ControllerPtr) malloc (sizeof(ControllerStr));
	temp_controller->readyQueue = Queue_construct();
	temp_controller->kbQueue = Queue_construct();
	temp_controller->hddQueue = Queue_construct();
	temp_controller->videoQueue = Queue_construct();
	temp_controller->idleProcess = pcbConstruct(500, -1);
	return temp_controller;
}


int main (int argc, char* argv[])
{
	int process_num;
	int kb_num;
	int io_num;
	int pc_num;
	
	if(argc == 9)
	{
		//printf("%s ", argv[1]);// -p
		process_num = (int) strtol(argv[2], NULL, 10);
		//printf("%d\n", process_num);// num of -p
		
		//printf("%s ", argv[3]);// -k
		kb_num = (int) strtol(argv[4], NULL, 10);
		//printf("%d\n", kb_num);// num of -k
		
		//printf("%s ", argv[5]); //-io
		io_num = (int) strtol(argv[6], NULL, 10);
		//printf("%d\n", io_num);
		
		//printf("%s ", argv[7]);// -pc
		pc_num = (int) strtol(argv[8], NULL, 10);
		//printf("%d\n", pc_num);
	}
	else
	{
		printf("You input the incorrect parameters. To run this program, it must have "
			   "these input paramters: \n"
			   "-p x -k x -io x -pc x\n"
			   "where 'x' is a number");
		return 0;
	}
	
	ControllerPtr controller = controllerConstruct();
	srand(time(NULL)); //Seeds the random number generator
	createProcesses(process_num, kb_num, io_num, pc_num, controller);
	
	printf("Process Summary\n");
	int i;
	for (i = 0; i < process_num; i++) {
		int type = controller->processList[i]->processType;
		printf("P%d, type %d, service calls [", controller->processList[i]->PID, type);
		int j;
		for (j = 0; j < 8; j++) {
			printf(" %d", controller->processList[i]->serviceCallValues[j]);
		}
		printf(" ]\n");
		Queue_add(controller->readyQueue, controller->processList[i]);
	}
	printf("\n");
	controller->runningProcess = Queue_remove(controller->readyQueue);
	printCurrentState(controller);
	
	startTimer(5);
	
	CpuPtr cpu = cpuConstruct(controller);
	cpuRun(cpu);
	
	pthread_exit(NULL);
	return 0;
}

void printCurrentState(ControllerPtr this) {
	int i;
	printf("RUNNING [ ");
	if (this->runningProcess->PID == 500) {
		printf("idle ");
	} else {
		printf("P%d ", this->runningProcess->PID);
	}
	printf("]\n");
	printf("READY_Q [ ");
	int pos = this->readyQueue->head;
	int size = this->readyQueue->count;
	int max = this->readyQueue->max;
	for (i = 0; i < size; i++) {
		if (pos >= max) {
			pos = 0;
		}
		printf("P%d ", this->readyQueue->pcbs[pos]->PID);
		pos++;
	}
	printf("]\n");
	printf("KB_Q    [ ");
	pos = this->kbQueue->head;
	size = this->kbQueue->count;
	max = this->kbQueue->max;
	for (i = 0; i < size; i++) {
		if (pos >= max) {
			pos = 0;
		}
		printf("P%d ", this->kbQueue->pcbs[pos]->PID);
		pos++;
	}
	printf("]\n");
	printf("HDD_Q   [ ");
	pos = this->hddQueue->head;
	size = this->hddQueue->count;
	max = this->hddQueue->max;
	for (i = 0; i < size; i++) {
		if (pos >= max) {
			pos = 0;
		}
		printf("P%d ", this->hddQueue->pcbs[pos]->PID);
		pos++;
	}
	printf("]\n");
	printf("VIDEO_Q [ ");
	pos = this->videoQueue->head;
	size = this->videoQueue->count;
	max = this->videoQueue->max;
	for (i = 0; i < size; i++) {
		if (pos >= max) {
			pos = 0;
		}
		printf("P%d ", this->videoQueue->pcbs[pos]->PID);
		pos++;
	}
	printf("]\n");
	printf("MUTEX_Q [ ");
	//printf("P%d", get_mutex_process());
	printf("]\n");
}


void scheduler(ControllerPtr this) {
	if (this->runningProcess->PID != 500) {
		Queue_add(this->readyQueue, this->runningProcess);
	}
	if (this->readyQueue->count > 0) {
		this->runningProcess = Queue_remove(this->readyQueue);
	} else {
		this->runningProcess = this->idleProcess;
	}
	printCurrentState(this);
}

void IO_block(ControllerPtr controller, int IODeviceID)
{
	if(IODeviceID == 1) // Send process to Keyboard blocking queue
	{
		Queue_add(controller->kbQueue, controller->runningProcess);
		printf("------------------------------\nP%d sent to KB_Q\n------------------------------\n",
			   controller->runningProcess->PID);
	}
	
	else if(IODeviceID == 2) //Send process to hdd blocking queue
	{
		Queue_add(controller->hddQueue, controller->runningProcess);
		printf("------------------------------\nP%d sent to HDD_Q\n------------------------------\n",
			   controller->runningProcess->PID);
	}
	else if(IODeviceID == 3) // Send process to video blocking queue
	{
		Queue_add(controller->videoQueue, controller->runningProcess);
		printf("------------------------------\nP%d sent to VIDEO_Q\n------------------------------\n",
			   controller->runningProcess->PID);
	}
	
	if (controller->readyQueue->count > 0) {
		controller->runningProcess = Queue_remove(controller->readyQueue);
	} else {
		controller->runningProcess = controller->idleProcess;
	}
	printCurrentState(controller);
}

void setProcessReady(ControllerPtr controller, int IODeviceID)
{
	if(IODeviceID == 1) //KB blocking queue returns process to ready queue.
	{
		PcbPtr temp_pcb = Queue_remove(controller->kbQueue);
		Queue_add(controller->readyQueue, temp_pcb);
		printf("P%d moved from KB_Q to READY_Q\n------------------------------\n", temp_pcb->PID);
	}
	else if(IODeviceID == 2) //HDD blocking queue returns process to ready queue.
	{
		PcbPtr temp_pcb = Queue_remove(controller->hddQueue);
		Queue_add(controller->readyQueue, temp_pcb);
		printf("P%d moved from HDD_Q to READY_Q\n------------------------------\n", temp_pcb->PID);
	}
	else if(IODeviceID == 3)
	{
		PcbPtr temp_pcb = Queue_remove(controller->videoQueue);
		Queue_add(controller->readyQueue, temp_pcb);
		printf("P%d moved from VIDEO_Q to READY_Q\n------------------------------\n", temp_pcb->PID);
	}
	printCurrentState(controller);
}

void createProcesses(int total_processes, int kb_amount, int io_amount, int pc_amount,
					 ControllerPtr controller)
{
	if (pc_amount > 1) {
		pc_amount = 1;
	}
	controller->processList = (PcbPtr*) malloc((total_processes + 2) * sizeof(PcbPtr));
	int cpu_bound_processes = total_processes - kb_amount - io_amount - (pc_amount * 2);
	int processID = 0;
	int index = 0;
	for(; index < cpu_bound_processes; index++)
	{
		controller->processList[processID] = pcbConstruct(processID, 0);
		processID++;
	}
	
	if(kb_amount > 0)
	{
		controller->processList[processID] = pcbConstruct(processID, 1);
		processID++;
	}
	
	if(io_amount > 2)
	{
		io_amount = 2;
	}
	
	for(index = 0; index < io_amount; index++)
	{
		//process types for IO start at 2, so index has two added to it for the correct io type
		controller->processList[processID] = pcbConstruct(processID, index + 2);
		processID++;
	}

	if (pc_amount > 0) {
		controller->processList[processID] = pcbConstruct(processID, 4);
		processID++;
		controller->processList[processID] = pcbConstruct(processID, 5);
	}

}