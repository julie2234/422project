/*
 *  controller.c
 *      GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *      TCSS 422, Spring 2013
 */

#include "device_io.h"

DeviceIOPtr device_io_contrustor(int io_interrupt_id, int io_process_id) {
       srand(time(NULL));
       
       DeviceIOPtr temp_dev_io = (DeviceIOPtr) malloc(sizeof(DeviceIOStr));
       temp_dev_io->io_interrupt_current_count = 0;
       temp_dev_io->io_interrupt_time = MIN_INTERRUPT_DELAY + rand() % MAX_INTERRUPT_DELAY;
       temp_dev_io->device_io_interrupt = io_interrupt_id;
       temp_dev_io->device_io_process = io_process_id;
       return temp_dev_io;
}


//Reset the io_interrupt_time to a new random value
//Reset the current_count
DeviceIOPtr devioReActivate(DeviceIOPtr temp_dev_io) {
     temp_dev_io->io_interrupt_time = MIN_INTERRUPT_DELAY + rand() % MAX_INTERRUPT_DELAY;
     temp_dev_io->io_interrupt_current_count = 0;
     return temp_dev_io;
}

//Interrupts the CPU
void interruptCpu(DeviceIOPtr temp_dev_io) {
     setInterrupt(temp_dev_io->device_io_interrupt,  temp_dev_io->device_io_process);
}

//a looping thread that runs until device io activity is set to 0
static void *deviceLoop(void* temp_dev_io_ptr) {
       DeviceIOPtr temp_dev_io = (DeviceIOPtr) temp_dev_io_ptr;
       while (temp_dev_io->io_interrupt_current_count++ != temp_dev_io->io_interrupt_time) {
             temp_dev_io->io_interrupt_current_count = temp_dev_io->io_interrupt_current_count % MAX_INTERRUPT_DELAY;
       }
       interruptCpu(temp_dev_io);
       return 0;
}

//Initializes the pthread
void startDeviceIO(DeviceIOPtr temp_dev_io) {
     devioReActivate(temp_dev_io);
     pthread_t device_thread;
     pthread_create(&device_thread, NULL, deviceLoop, (void *) temp_dev_io);
}


/*
int main(void) {
      startDeviceIO();
      pthread_exit(NULL);
}
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
