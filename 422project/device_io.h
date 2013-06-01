
#ifndef DEVICE_IO_H

#include "CPU.h"
#define MAX_INTERRUPT_DELAY     100;
typedef struct DeviceIO {
        int io_interrupt_current_count;
        int io_interrupt_time;
        int io_interrupt;
        CpuPtr io_cpu;
} DeviceIOStr;

typedef DeviceIOStr* DeviceIOPtr;

DeviceIOPtr initialize(CpuPtr cpu);
int devio_sleep(DeviceIOPtr temp_dev_io);
int devio_awake(DeviceIOPtr temp_dev_io);
void increment(DeviceIOPtr temp_dev_io);
int interrupt_cpu(DeviceIOPtr temp_dev_io);
#endif
