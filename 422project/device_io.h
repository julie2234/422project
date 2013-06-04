/*
 *  controller.c
 *      GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *      TCSS 422, Spring 2013
 */

#ifndef DEVICE_IO_H
#define DEVICE_IO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_INTERRUPT_DELAY     100;
#define MIN_INTERRUPT_DELAY     100;

typedef struct DeviceIO {
        int io_interrupt_current_count;
        int io_interrupt_time;
        int device_io_interrupt;
        int device_io_process;
        struct PcbStr* io_pcb;
} DeviceIOStr;
typedef DeviceIOStr* DeviceIO;

void startDevice();
#endif
