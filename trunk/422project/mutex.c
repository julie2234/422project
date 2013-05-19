/*
 *  mutex.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "mutex.h"
#include <stdio.h>
#include <stdlib.h>

MutexPtr mutexConstruct() {
	MutexPtr temp_mutex = (MutexPtr) malloc (sizeof(MutexStr));
	return temp_mutex;
}

