/*
 *  CPU.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "CPU.h"
#include <stdio.h>
#include <stdlib.h>

CpuPtr cpuConstruct() {
	CpuPtr temp_cpu = (CpuPtr) malloc (sizeof(CpuStr));
	return temp_cpu;
}

