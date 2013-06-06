/*
 *  controller.h
 *	GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "PCB.h"
#include "process.h"
#include "timer.h"
#include "queue.h"

typedef struct controller_str {
	PcbPtr* processList;
	QueuePtr readyQueue;
	QueuePtr kbQueue;
	QueuePtr videoQueue;
	QueuePtr hddQueue;
	PcbPtr runningProcess;
	PcbPtr interruptedProcess;
	PcbPtr idle_process;
} ControllerStr;

typedef ControllerStr* ControllerPtr;

ControllerPtr controllerConstruct();
void timeEndInterrupt();
void scheduler(ControllerPtr this);
void IO_block(ControllerPtr controller, int IODeviceID);
void setProcessReady(ControllerPtr controller, int IODeviceID);
void createProcesses(int total_processes, int kb_amount, int io_amount, int pc_amount,
		ControllerPtr controller);
void printCurrentState(ControllerPtr this);

#endif

