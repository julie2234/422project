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

#define MAX_INTERRUPT_DELAY     10000;
#define MIN_INTERRUPT_DELAY     1000;

typedef struct DeviceIO {
        int io_interrupt_current_count;
        int io_interrupt_time;
        int device_io_interrupt;
        int device_io_process;
        struct PcbStr* io_pcb;
} DeviceIOStr;
typedef DeviceIOStr* DeviceIO;

DeviceIO device_io_constructor(int io_interrupt_id, int io_process_id);
DeviceIO devioReActivate(DeviceIO temp_dev_io);
void interruptCpu(DeviceIO temp_dev_io);
static void *deviceLoop(void* temp_dev_io_ptr);
void startDeviceIO(DeviceIO temp_dev_io);




DeviceIO device_io_constructor(int io_interrupt_id, int io_process_id);
DeviceIO devioReActivate(DeviceIO temp_dev_io);
void interruptCpu(DeviceIO temp_dev_io);
static void *deviceLoop(void* temp_dev_io_ptr);
void startDeviceIO(DeviceIO temp_dev_io);
#endif
