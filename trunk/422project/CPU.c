/*
 *  CPU.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "CPU.h"

int interruptFlag = 0;
int interruptList[5]; //For interrupts that happen during other interrupts
int interruptIndex = 0; //The index for the interrupt list

CpuPtr cpuConstruct(ControllerPtr passedInController)
{
	CpuPtr temp_cpu = (CpuPtr) malloc (sizeof(CpuStr));
	temp_cpu->controller = passedInController;
	temp_cpu->current_pcb = passedInController->processList[0];
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
		while(interruptFlag == 1)
		{
			if(interruptIndex == 0) //Check to see if there are more interrupts waiting
			{
				interruptFlag = 0;
			}

			determineInterrupt(interruptList[interruptIndex]);

			if (interruptList[interruptIndex] == 8)
			{
				scheduler(cpu->controller);
			}
		}
		nanosleep(&timePerTick, &timeRemaining);
		PC++;
		if(PC == max - 1)
		{
			PC = 0;
		}

		//This could be unnecessary, but I don't think
		//we want to have to worry about what the PC value is
		//for a process somewhere else when this process get's interrupted.
		cpu->current_pcb->currentCount = PC;

		int index = 0;


		for(; index < 8; index++)
		{
			if(cpu->current_pcb->serviceCallValues[index] == PC)
			{
				//call deviceIO service routine
				determineSystemCall(cpu->current_pcb);
				printf(" PC is %d \n", PC);
			}
		}
	}
	return;
}

void setInterrupt(int interruptID)
{
	interruptFlag = 1;
	interruptIndex++;
	interruptList[interruptIndex] = interruptID;

	return;
}

void determineSystemCall(PcbPtr current_pcb)
{
	int process_type = current_pcb->processType;
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
			startKeyboardListener(current_pcb->PID);
			break;
		}
		case 2:
		{
			//This is HDD_io, so this can go to the device_io class/source file
			//(whatever you want to call it).
			printf("HDD IO");
			break;
		}
		case 3:
		{
			//Video_io, same idea as HDD_io, but goes to it's own source/thread.
			printf("Video IO");
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

void determineInterrupt(int interruptType)
{
	switch(interruptType)
	{
		case 0: // timer interrupt
		{
			//do the timer interrupt functions
			break;
		}

		case 1: //hdd interrupt
		{
			//do the hdd interrupt functions
			break;
		}

		case 2: //video interrupt
		{
			//do the video interrupt functions
			break;
		}

		default:
		{
			//do nothing
		}
	}
}

