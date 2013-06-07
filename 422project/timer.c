/*
 *  timer.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */


#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#include "timer.h"
#include "CPU.h"

int continue_ticks = 1;



//This function goes to sleep for the specified quanta, wakes up, calls a function,
//and goes back to sleep continuously until the program stops it from sleeping.
void *tickingTimer(void* quanta)
{
	int loops = 0;
	while(continue_ticks)
	{
		sleep((int) quanta);
		setInterrupt(0, -1);
		//notify CPU/Controller, maybe something like
		//interruptNotify() that would simply point out that it is
		//time for an interrupt.
		
		loops++;
		if(loops >= cycles)
		{
			continue_ticks = 0;
		}

	}

	run_flag = 0;

	return 0;
}

//This function starts the the timer ticking down for interrupts and whatnot.
void startTimer(int quanta)
{
	pthread_t thread;
	pthread_create(&thread, NULL, tickingTimer, (void *) quanta);
}

//int main(void)
//{
//	startTimer(4);
//  return 0;
//}
