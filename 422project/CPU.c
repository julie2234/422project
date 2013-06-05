/*
 *  CPU.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "CPU.h"

int interruptFlag = 0;
int interruptList[5]; //For interrupts that happen during other interrupts

//This is a "parallel" array that holds a list of processes that correspond to the interrupt
int interruptProcessList[5];
int interruptListSize = 0; //The index for the interrupt list

CpuPtr cpuConstruct(ControllerPtr passedInController)
{
	CpuPtr temp_cpu = (CpuPtr) malloc (sizeof(CpuStr));
	temp_cpu->controller = passedInController;
	temp_cpu->current_pcb = passedInController->runningProcess;
	temp_cpu->hdd_device_io = device_io_constructor(2, -1);
	temp_cpu->video_device_io = device_io_constructor(3, -1);
	return temp_cpu;
}

//http://linux.die.net/man/2/nanosleep
//Read this to know what nanosleep does.
void cpuRun(CpuPtr cpu)
{
	int PC = cpu->current_pcb->currentCount;
	int max = MAX_PC
	struct timespec timePerTick, timeRemaining;
	timePerTick.tv_sec = 0;
	timePerTick.tv_nsec = TICK_TIME;

	while(PC < max)
	{
		PC++;
		if(PC == max - 1)
		{
			PC = 0;
		}
		//This could be unnecessary, but I don't think
		//we want to have to worry about what the PC value is
		//for a process somewhere else when this process get's interrupted.
		cpu->current_pcb->currentCount = PC;

		int interruptIndex = 0;
		while(interruptFlag == 1)
		{
			determineInterrupt(cpu, interruptList[interruptIndex], interruptProcessList[interruptIndex]);

//			if (interruptList[interruptIndex] == 8)
//			{
//				scheduler(cpu->controller);
//			}

			interruptIndex++;
			if(interruptListSize == interruptIndex) //Check to see if there are more interrupts waiting
			{
				interruptFlag = 0;
				interruptListSize = 0;
			}
		}
		nanosleep(&timePerTick, &timeRemaining);

		int index = 0;


		for(; index < 8; index++)
		{
			if(cpu->current_pcb->serviceCallValues[index] == PC)
			{
				//call deviceIO service routine
				determineSystemCall(cpu);
			}
		}
	}
	return;
}

void setInterrupt(int interruptID, int processID)
{
	interruptFlag = 1;
	interruptList[interruptListSize] = interruptID;
	interruptProcessList[interruptListSize] = processID;
	interruptListSize++;

	return;
}

void determineSystemCall(CpuPtr cpu)
{
	int process_type = cpu->controller->runningProcess->processType;
	switch(process_type)
	{
		case 0:
		{
			//This is a compute bound process, I don't think we need to do anything here
			break;
		}
		case 1:
		{
			//This is keyboard_io, which it blocks, waiting for the user to hit a key.
			startKeyboardListener(cpu->current_pcb->PID);
			IO_block(cpu->controller, 1);

			break;
		}
		case 2:
		{
			//This is HDD_io, so this can go to the device_io class/source file
			//(whatever you want to call it).
			cpu->hdd_device_io->device_io_process = cpu->controller->runningProcess;
			startDeviceIO(cpu->hdd_device_io);
			IO_block(cpu->controller, 2);
			break;
		}
		case 3:
		{
			//Video_io, same idea as HDD_io, but goes to it's own source/thread.
			cpu->video_device_io->device_io_process = cpu->controller->runningProcess;
			startDeviceIO(cpu->video_device_io);
			IO_block(cpu->controller, 3);
			break;
		}
		case 4:
		{
			//producer, not sure yet what is going to happen here
			break;
		}
		case 5:
		{
			//consumer, same as above
			break;
		}

		default:
		{
			//do nothing
		}
	}
}

void determineInterrupt(CpuPtr cpu, int interruptType, int processID)
{
	switch(interruptType)
	{
		case 0: // timer interrupt
		{
			printf("Timer Interrupt\n");
			scheduler(cpu->controller);
			break;
		}

		case 1: //KB interrupt
		{
			char key_press = getKeyPress();
      printf("K I/O - %c key pressed, P%d interrupted", key_press, processID);
			//printf("You pressed %c\n", key_press);
			//printf("Which is %d in ascii\n", key_press);
			setProcessReady(cpu->controller, 1);
			break;
		}

		case 2: //hdd interrupt
		{
      printf("HDD I/O - P%d interrupted, data transfer", processID);
			//printf("HDD Device done transfering data, now giving data to process\n");
			setProcessReady(cpu->controller, 2);

			break;
		}

		case 3: //video interrupt
		{
      printf("Vidio I/O - P%d interrupted, data transfer from Video I/O", processID);
			//printf("Data done being transfered to video output device\n");
			setProcessReady(cpu->controller, 3);
			break;
		}


		default:
		{
			//do nothing
		}
	}
	interruptFlag = 0;
}

