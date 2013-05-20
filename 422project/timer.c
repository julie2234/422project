/*
 *  timer.c
 *
 *  Created on: May 20, 2013
 *      Author: Tyler Simrell
 */


#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int continue_ticks = 1;

//This function was just a test to see if functions could be called from within a threaded
//function. It will be replaced when we decide how the timer will interact with the
//controller.
void printSomething()
{
	printf("Time ended!\n");
}

//This function goes to sleep for the specified quanta, wakes up, calls a function,
//and goes back to sleep continuously until the program stops it from sleeping.
void *tickingTimer(int quanta)
{
	printf("in the thread\n");
	int loops = 0;
	while(continue_ticks)
	{
		sleep(quanta);
		printSomething();
		//notify CPU/Controller, maybe something like
		//interruptNotify() that would simply point out that it is
		//time for an interrupt.
		loops++;
		if(loops > 5)
		{
			continue_ticks = 0;
		}
	}
}

//This function starts the the timer ticking down for interrupts and whatnot.
void startTimer(int quanta)
{
	pthread_t thread;
	pthread_create(&thread, NULL, tickingTimer, (void *) quanta);

	pthread_exit(NULL);
}

void main(void)
{
	startTimer(4);
}
