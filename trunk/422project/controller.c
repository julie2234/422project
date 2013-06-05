/*
 *  controller.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
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
	return temp_controller;
}


int main (int argc, char* argv[])
{
	int process_num;
	int kb_num;
	int io_num;
	int pc_size;

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
		pc_size = (int) strtol(argv[8], NULL, 10);
		//printf("%d\n", pc_size);
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
	createProcesses(process_num, kb_num, io_num, controller);

//	//just for testing
//	controller->processList[0] = pcbConstruct(0, 1);
//	controller->processList[1] = pcbConstruct(1, 3);
//	controller->processList[2] = pcbConstruct(2, 2);
//	controller->processList[3] = pcbConstruct(3, 4);
	

	printf("Process Summary\n");
	int i;
	for (i = 0; i < process_num; i++)
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
	return 0;
}


void scheduler(ControllerPtr this)
{
	printf("Process %d is out of time.", this->runningProcess->PID);
	Queue_add(this->readyQueue, this->runningProcess);
	PcbPtr process = Queue_remove(this->readyQueue);
	printf("\nP%d has been loaded into the registers and is now running \n", process->PID);
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

void setProcessReady(ControllerPtr controller, int IODeviceID)
{
        if(IODeviceID == 1) //KB blocking queue returns process to ready queue.
        {
                PcbPtr temp_pcb = Queue_remove(controller->kbQueue);
                Queue_add(controller->readyQueue, temp_pcb);
                printf("Process %d removed from keyboard blocked queue and added to the ready queue\n", temp_pcb->PID);
        }
        else if(IODeviceID == 2) //HDD blocking queue returns process to ready queue.
        {
                PcbPtr temp_pcb = Queue_remove(controller->hddQueue);
                Queue_add(controller->readyQueue, temp_pcb);
                printf("Process %d removed from HDD blocked queue and added to the ready queue\n", temp_pcb->PID);
        }
        else if(IODeviceID == 3)
        {
                PcbPtr temp_pcb = Queue_remove(controller->videoQueue);
                Queue_add(controller->readyQueue, temp_pcb);
                printf("Process %d removed from video blocked queue and added to the ready queue\n", temp_pcb->PID);
        }
}

void createProcesses(int total_processes, int kb_amount, int io_amount, ControllerPtr controller)
{
	controller->processList = (PcbPtr*) malloc((total_processes + 1) * sizeof(PcbPtr));
	int cpu_bound_processes = total_processes - kb_amount - io_amount;
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
}


