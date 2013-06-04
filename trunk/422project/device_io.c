#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include "device_io.h"
//#include "CPU.h"

DeviceIO initialize() {
       srand(time(NULL));
       
       DeviceIO temp_dev_io = (DeviceIO) malloc(sizeof(DeviceIOStr));
       temp_dev_io->io_interrupt_current_count = 0; 
       temp_dev_io->io_interrupt_time = 100 + rand() % MAX_INTERRUPT_DELAY;
       temp_dev_io->io_interrupt = 1;
       //temp_dev_io->io_cpu = cpu;
       return temp_dev_io;
}



void devioReActivate(DeviceIO temp_dev_io) {
     temp_dev_io->io_interrupt_time = 100 + rand() % MAX_INTERRUPT_DELAY;
     temp_dev_io->io_interrupt_current_count = 0;
}
/*
void devLoop(DeviceIO temp_dev_io) {
     while(++temp_dev_io->io_interrupt_current_count != temp_dev_io->io_interrupt_time) {
          temp_dev_io->io_interrupt_current_count = temp_dev_io->io_interrupt_current_count % MAX_INTERRUPT_DELAY;
     }
     //interrupt_cpu();
}

void int interruptCpu(DeviceIO temp_dev_io) {
     cpu->iterruptFlag = temp_dev_io->io_interrupt;
     
}
*/
static void *deviceLoop(void* num) {
     DeviceIO temp_dev_io;
     temp_dev_io = initialize();
     //while() {
          while(++temp_dev_io->io_interrupt_current_count != temp_dev_io->io_interrupt_time) {
               printf("%d",temp_dev_io->io_interrupt_current_count);
               temp_dev_io->io_interrupt_current_count = temp_dev_io->io_interrupt_current_count % MAX_INTERRUPT_DELAY;
          }  
     //}
     return 0;
}

void startDeviceIO(int num) {
     pthread_t device_thread;
     pthread_create(&device_thread, NULL, deviceLoop, (void *) num);
}

int main(void) {
      startDeviceIO(5);
      pthread_exit(NULL);
}

/*
int increment(int data_count) {
    temp_dev_io->current_count = ++temp_dev_io->current_count % MAX_INTERRUPT_DELAY;
    if(temp_dev_io->current_count == 0) {
          temp_dev_io->current_count = 1;
     }
     if (temp_dev_io->current_count == temp_dev_io->io_interrupt_time) {
          interrupt_cpu(temp_dev_io);                       
     }
    return data_count;
}
*/
