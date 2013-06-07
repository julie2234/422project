/*
 *  process.h
  *	GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef PROCESS_H
#define PROCESS_H

//The Processs type list
#define CPU_BOUND 0;
#define KEYBOARD_IO 1;
#define HDD_IO 2;
#define VIDEO_IO 3;
#define PRODUCER 4;
#define CONSUMER 5;

typedef struct process_str {
	int processType;
} ProcessStr;

typedef ProcessStr* ProcessPtr;
ProcessPtr processContruct(int the_processType, int the_PID);

#endif
