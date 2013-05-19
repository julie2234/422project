/*
 *  process.h
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef PROCESS_H
#define PROCESS_H

// Process Types
#define KEYBOARD	0
#define COMPUTE		1
#define IO			2
#define PRODUCER	3
#define CONSUMER	4

typedef struct process_str {
	int processType;
} ProcessStr;

typedef ProcessStr* ProcessPtr;


#endif