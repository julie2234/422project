/*
 *  queue.h
 *  GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "PCB.h"

#define NULL_POINTER -1;
#define QUEUE_SIZE 20;

typedef struct queue_str {
	int head;
	int count;
	int max;
	PcbPtr pcbs[20];
} QueueStr;

typedef struct queue_str* QueuePtr;

/*
 * Construct a new Queue with given inital capacity.
 */
QueuePtr Queue_construct();

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

PcbPtr Queue_peek(QueuePtr queue);


/*typedef struct queue_str {
 int head;
 int count;
 int max;
 PcbPtr * pcbs;
 } QueueStr;
 
 typedef struct queue_str* QueuePtr;
 
QueuePtr Queue_construct(int init_cap);

void     Queue_destruct(QueuePtr queue);

int      Queue_size(QueuePtr queue);

int      Queue_add(QueuePtr queue, PcbPtr pcb);

PcbPtr   Queue_remove(QueuePtr queue);

PcbPtr   Queue_peek(QueuePtr queue);

void     Queue_clear(QueuePtr queue);

void     Queue_resize(QueuePtr queue, int new_size);*/

#endif

