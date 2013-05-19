/*
 *  condVar.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "condVar.h"
#include <stdio.h>
#include <stdlib.h>

CondVarPtr condVarConstruct() {
	CondVarPtr temp_condVar = (CondVarPtr) malloc (sizeof(CondVarStr));
	return temp_condVar;
}

