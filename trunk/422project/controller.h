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
#include "device_io.h"
#include "CPU.h"

typedef struct controller_str {
	PcbPtr processList[4];
	QueuePtr readyQueue;
	QueuePtr kbQueue;
	QueuePtr videoQueue;
	QueuePtr hddQueue;
	PcbPtr runningProcess;
	PcbPtr interruptedProcess;
	DeviceIOPtr hddDeviceIO;
	DeviceIOPtr videoDeviceIO;
} ControllerStr;

typedef ControllerStr* ControllerPtr;

ControllerPtr controllerConstruct();
void timeEndInterrupt();
void scheduler(ControllerPtr this);
void IO_block(ControllerPtr controller, int IODeviceID);

#endif

