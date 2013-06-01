#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include "device_io.h"
#include "CPU.h"

DeviceIO initialize(CpuPtr cpu) {
       srand(time(NULL)); //random number generator seed.
       
       DeviceIO temp_dev_io = (DeviceIO) malloc(sizeof(DeviceIOStr));
       temp_dev_io->io_interrupt_current_count = 0; 
       temp_dev_io->io_interrupt_time = rand() % MAX_INTERRUPT_DELAY;
       temp_dev_io->io_interrupt = 1;
       temp_dev_io->io_cpu = cpu;
       return temp_dev_io;
}

int devio_sleep(DeviceIO temp_dev_io) {
     temp_dev_io->io_interrupt_time = 0;
     return 0;
}

int devio_awake(DeviceIO temp_dev_io) {
     temp_dev_io->io_interrupt_time = rand() % MAX_INTERRUPT_DELAY;
     temp_dev_io->io_interrupt_current_count = 0; 
     return 0;
}

void increment(DeviceIO temp_dev_io) {
     //!!!While loop looks like a bad idea, consider using another method!!!
     while(++temp_dev_io->io_interrupt_current_count != temp_dev_io->io_interrupt_time) {
          temp_dev_io->io_interrupt_current_count = temp_dev_io->io_interrupt_current_count % MAX_INTERRUPT_DELAY;
     }
     interrupt_cpu(temp_dev_io);
     return;
}

int interrupt_cpu(DeviceIO temp_dev_io) {
     //Needs to interrupt CPU
     //Need to implement CPU interrupt in CPU.c
     return 0;
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
