/*
 *  CPU.h
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "controller.h"
#include "PCB.h"
#include "keyboard_io.h"


#define TICK_TIME 100000000L;
#define MAX_PC 1000;

#define TIMER_INTERRUPT = 0;
#define HDD_INTERRUPT = 1;
#define VIDEO_INTERRUPT = 2;
#define CPU_H

typedef struct cpu_str
{
	PcbPtr current_pcb;
	ControllerPtr controller;
	//list of possible interrupts to know what to do when an interrupt occurs.

} CpuStr;

typedef CpuStr* CpuPtr;

CpuPtr cpuConstruct(ControllerPtr controller);
void cpuRun(CpuPtr cpu);
void determineSystemCall(CpuPtr cpu);
void determineInterrupt(CpuPtr cpu, int interruptType, int processID);
void setInterrupt(int interruptID, int processID);

#endif

