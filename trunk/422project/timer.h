/*
 *  timer.h
 *	GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef TIMER_H
#define TIMER_H

int cycles;

void *tickingTimer(void* quanta);
void startTimer(int quanta);

#endif /* TIMER_H_ */
