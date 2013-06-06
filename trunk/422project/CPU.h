/*
 *  CPU.h
 *      GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *      TCSS 422, Spring 2013
 */

#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PCB.h"
#include "keyboard_io.h"
#include "device_io.h"


#define TICK_TIME 100000000L;
#define MAX_PC 100;

#define TIMER_INTERRUPT = 0;
#define HDD_INTERRUPT = 1;
#define VIDEO_INTERRUPT = 2;
#define CPU_H

int run_flag;

typedef struct cpu_str
{
	PcbPtr current_pcb;
	ControllerPtr controller;
	DeviceIO hdd_device_io;
	DeviceIO video_device_io;
	
} CpuStr;

typedef CpuStr* CpuPtr;

CpuPtr cpuConstruct(ControllerPtr controller);
void cpuRun(CpuPtr cpu);
void determineSystemCall(CpuPtr cpu);
void determineInterrupt(CpuPtr cpu, int interruptType, int processID);
void setInterrupt(int interruptID, int processID);

#endif