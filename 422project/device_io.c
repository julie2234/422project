#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "device_io.h"

DeviceIO initialize() {
       srand(time(NULL));
       
       DeviceIO temp_dev_io = (DeviceIO) malloc(sizeof(DeviceIOStr));
       temp_dev_io->io_interrupt_current_count = 0; 
       temp_dev_io->io_interrupt_time = MIN_INTERRUPT_DELAY + rand() % MAX_INTERRUPT_DELAY;
       temp_dev_io->device_io_interrupt = 1;
       //temp_dev_io->io_cpu = cpu;
       return temp_dev_io;
}

DeviceIO devioReActivate(DeviceIO temp_dev_io) {
     temp_dev_io->io_interrupt_time = MIN_INTERRUPT_DELAY + rand() % MAX_INTERRUPT_DELAY;
     temp_dev_io->io_interrupt_current_count = 0;
     return temp_dev_io;
}

void interruptCpu() {
     //CHECK TO SEE IF CPU IS ALREADY INTERRUPTED
     setInterrupt(1, process_waiting);
}

static void *deviceLoop() {
     DeviceIO temp_dev_io;
     temp_dev_io = initialize();
     while(++temp_dev_io->io_interrupt_current_count != temp_dev_io->io_interrupt_time || temp_dev_io->device_io_interrupt) {
          printf("%d",temp_dev_io->io_interrupt_current_count);
          temp_dev_io->io_interrupt_current_count = temp_dev_io->io_interrupt_current_count % MAX_INTERRUPT_DELAY;
     }  
     interruptCpu();
     return 0;
}

void startDeviceIO() {
     pthread_t device_thread;
     pthread_create(&device_thread, NULL, deviceLoop, NULL);
}

int main(void) {
      startDeviceIO();
      pthread_exit(NULL);
}