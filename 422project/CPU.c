/*
 *  CPU.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "CPU.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TICK_TIME 100000000L;
#define MAX_PC 10000;

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
	int PC = 0;
	int max = MAX_PC
	struct timespec timePerTick, timeRemaining;
	timePerTick.tv_sec = 0;
	timePerTick.tv_nsec = TICK_TIME;

	while(PC < max)
	{
		nanosleep(&timePerTick, &timeRemaining);
		PC++;
		//Insert check for traps here
//		printf("%d\n", PC);
	}

	return;
}

