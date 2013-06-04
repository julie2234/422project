/*
 *  controller.c
 *      GPOS Scheduler Simulation
 *  Team 8: Simerell, Trottier, Morris, Impola
 *      TCSS 422, Spring 2013
 */


#include "device_io.h"

DeviceIO initialize() {
       srand(time(NULL));
       
       DeviceIO temp_dev_io = (DeviceIO) malloc(sizeof(DeviceIOStr));
       temp_dev_io->io_interrupt_current_count = 0; 
       temp_dev_io->io_interrupt_time = MIN_INTERRUPT_DELAY + rand() % MAX_INTERRUPT_DELAY;
       temp_dev_io->device_io_interrupt = 1;
       temp_dev_io->device_io_activity = 1;
       return temp_dev_io;
}


//Reset the io_interrupt_time to a new random value
//Reset the current_count
DeviceIO devioReActivate(DeviceIO temp_dev_io) {
     temp_dev_io->io_interrupt_time = MIN_INTERRUPT_DELAY + rand() % MAX_INTERRUPT_DELAY;
     temp_dev_io->io_interrupt_current_count = 0;
     return temp_dev_io;
}

//Interrupts the CPU
void interruptCpu() {
     //CHECK TO SEE IF CPU IS ALREADY INTERRUPTED
     //setInterrupt(1, process_waiting);
}

//a looping thread that runs until device io activity is set to 0
static void *deviceLoop() {
     DeviceIO temp_dev_io;
     temp_dev_io = initialize();
     while(temp_dev_io->device_io_activity) {
          while (++temp_dev_io->io_interrupt_current_count != temp_dev_io->io_interrupt_time) {
                temp_dev_io->io_interrupt_current_count = temp_dev_io->io_interrupt_current_count % MAX_INTERRUPT_DELAY;
          }
          interruptCpu();
          temp_dev_io = devioReActivate(temp_dev_io);
     }  
     return 0;
}

//Stops/Kills the running thread
void killDeviceIO(DeviceIO temp_dev_io) {
     temp_dev_io->device_io_activity = 0;
}

//Initializes the pthread
void startDeviceIO() {
     pthread_t device_thread;
     pthread_create(&device_thread, NULL, deviceLoop, NULL);
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