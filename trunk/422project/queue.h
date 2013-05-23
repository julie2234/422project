#ifndef QUEUE_H
#define QUEUE_H

#include "PCB.h"

#define NULL_POINTER -1;

typedef struct queue_str {
	int head;
	int count;
	int max;
	PcbPtr * pcbs;
} QueueStr;

typedef struct queue_str* QueuePtr;

/*
 * Construct a new Queue with given inital capacity.
 */
QueuePtr Queue_construct(int init_cap);

/*
 * Destruct a given queue-by freeing the internal array as well as the queue itself. 
 */
void     Queue_destruct(QueuePtr queue);

/*
 * Retrieve the size of the given queue. 
 */
int      Queue_size(QueuePtr queue);

/*
 * Add a PCB to the queue.
 */
int      Queue_add(QueuePtr queue, PcbPtr pcb);

/*
 * Remove a PCB from the head of a queue.
 */
PcbPtr   Queue_remove(QueuePtr queue);

/*
 * Retrieve, but do not remove, a PCB from the head of the queue.
 */
PcbPtr   Queue_peek(QueuePtr queue);

/*
 * Clear all elements from a queue. DOES NOT CHANGE CAPACITY.
 */
void     Queue_clear(QueuePtr queue);

/*
 * (INTERNAL USE ONLY) Resize the circular queue.
 */
void     Queue_resize(QueuePtr queue, int new_size);

#endif

