#define MAX_INTERRUPT_DELAY     100;

typedef struct DeviceIO {
        int io_interrupt_current_count;
        int io_interrupt_time;
        int io_interrupt;
        struct CpuStr* io_cpu;
} DeviceIOStr;
typedef DeviceIOStr* DeviceIO;
