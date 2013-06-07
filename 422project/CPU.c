/*
 *  CPU.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "CPU.h"
#include "prod_cons.h"

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
	int last_PID = 0;
	int PC = cpu->controller->runningProcess->currentCount;
	int max = MAX_PC
	struct timespec timePerTick, timeRemaining;
	timePerTick.tv_sec = 0;
	timePerTick.tv_nsec = TICK_TIME;
	
	while(PC < max && run_flag == 1)
	{
		PC++;
		if(PC == max - 1)
		{
			PC = 0;
		}
		//This could be unnecessary, but I don't think
		//we want to have to worry about what the PC value is
		//for a process somewhere else when this process get's interrupted.
		if (cpu->controller->runningProcess->processType < 4)
			cpu->controller->runningProcess->currentCount = PC;
		
		int interruptIndex = 0;
		while(interruptFlag == 1 && run_flag == 1)
		{
			determineInterrupt(cpu, interruptList[interruptIndex], interruptProcessList[interruptIndex]);
			
			interruptIndex++;
			if(interruptListSize == interruptIndex) //Check to see if there are more interrupts waiting
			{
				interruptFlag = 0;
				interruptListSize = 0;
			}
		}
		nanosleep(&timePerTick, &timeRemaining);
		
		int index = 0;

		if (cpu->controller->runningProcess->processType == 4 && (last_PID != cpu->controller->runningProcess->processType || cpu->controller->readyQueue->count == 1)) {
			Producer_tick(cpu);
			last_PID = cpu->controller->runningProcess->processType;
		} else if (cpu->controller->runningProcess->processType == 5 && (last_PID != cpu->controller->runningProcess->processType || cpu->controller->readyQueue->count == 1)) {
			Consumer_tick(cpu);
			last_PID = cpu->controller->runningProcess->processType;
		} else if (cpu->controller->runningProcess->processType < 4) {
			last_PID = cpu->controller->runningProcess->processType;
			for(; index < 8 && run_flag == 1; index++)
			{
				if(cpu->controller->runningProcess->serviceCallValues[index] == PC)
				{
					//call deviceIO service routine
					determineSystemCall(cpu);
				}
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
			printf("------------------------------\nTimer Interrupt\n------------------------------\n");
			scheduler(cpu->controller);
			break;
		}
			
		case 1: //KB interrupt
		{
			char key_press = getKeyPress();
			printf("------------------------------\nKB I/O Interrupt - %c key pressed, ", key_press);
			setProcessReady(cpu->controller, 1);
			break;
		}
			
		case 2: //hdd interrupt
		{
			printf("------------------------------\nHDD I/O Interrupt, ");
			setProcessReady(cpu->controller, 2);
			
			break;
		}
			
		case 3: //video interrupt
		{
			printf("------------------------------\nVIDEO I/O Interrupt, ");
			setProcessReady(cpu->controller, 3);
			break;
		}
			
			
		default:
		{
			//do nothing
		}
	}
	//interruptFlag = 0;
}
