/*
 *  CPU.h
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef CPU_H
#define CPU_H

typedef struct cpu_str
{
	PcbPtr current_pcb;
	ControllerPtr controller;
	//list of possible interrupts to know what to do when an interrupt occurs.

} CpuStr;

typedef CpuStr* CpuPtr;

CpuPtr cpuConstruct(ControllerPtr controller);

#endif

