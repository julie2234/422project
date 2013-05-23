#include "queue.h"
#include "PCB.h"
#include <stdlib.h>
#include <stdio.h>

QueuePtr Queue_construct(int init_cap) {
	QueuePtr newPtr;
	if (init_cap < 1)
		init_cap = 1;
	newPtr = (QueuePtr) malloc (sizeof(QueueStr));
	newPtr->head = 0;
	newPtr->count = 0;
	newPtr->max = init_cap;
	// Create the initial capacity array of PcbPtr.
	newPtr->pcbs = (PcbPtr*) malloc (sizeof(PcbStr) * init_cap);
	return newPtr;
}

void Queue_destruct(QueuePtr queue) {
	if (queue == 0)
		return;
	free (queue->pcbs);
	free (queue);
}

int Queue_size(QueuePtr queue) {
	if (queue == 0)
		return NULL_POINTER;
	return queue->count;
}

int Queue_add(QueuePtr queue, PcbPtr pcb) {
	int pos;
	if (queue == 0 || pcb == 0)
		return NULL_POINTER;
	// Resize if need be
	if (queue->count + 1 == queue->max)
		Queue_resize(queue, queue->max * 2);
	// Tail is where the pcb should be added (circular queue). Because the check to the queue size
	// before this line, the very last memory position will never be taken up.
	pos = (queue->head + queue->count) % queue->max;
	*(queue->pcbs+pos) = pcb;
	queue->count++;
	//printf("\nAdded a new element[%d/%d] at position[%d]", queue->count, queue->max, pos);
	return queue->count-1;
}

PcbPtr Queue_remove(QueuePtr queue) {
	int pos;
	if (queue == 0 || queue->count == 0)
		return 0;
	queue->count--;
	pos = queue->head;
	queue->head = (queue->head + 1) % queue->max;
	//printf("\nRemoved an element[%d/%d] at position[%d]", queue->count, queue->max, pos);
	return *queue->pcbs+pos;
}

void Queue_resize(QueuePtr queue, int new_size) {
	int i;
	int mod_i;
	int before;
	int after;
	PcbPtr* newAry;
	before = queue->max;
	after = new_size;
	newAry = (PcbPtr*) malloc(sizeof(PcbStr) * new_size);
	for (i = 0, mod_i = queue->head; i < queue->count; i++, mod_i=(mod_i+1)%queue->max) {
		*(newAry+i) = *(queue->pcbs+mod_i);
	}
	free(queue->pcbs);
	queue->pcbs = newAry;
	queue->max = new_size;
	queue->head = 0;
	//printf("\nHad to resize... from[%d] to[%d]", before, after);
}

PcbPtr Queue_peek(QueuePtr queue) {
	int pos;
	if (queue == 0 || queue->count == 0)
		return 0;
	pos = queue->head;
	return *queue->pcbs+pos;
}

void Queue_clear(QueuePtr queue) {
	if (queue == 0)
		return;
	queue->count = 0;
	queue->head = 0;
}

/*
int main() {

	PcbStr pcb1;
	PcbPtr pcb2;
	int i;
	int mod_i;
	QueuePtr ptr = Queue_construct(5);
	
	printf("\ncurrent count: %d", Queue_size(ptr));
	// Add 4 elements so as to not make it extend.
	for(i = 0; i < 4; i++) {
		pcb2 = (PcbPtr) malloc (sizeof(PcbStr));
		pcb2->PID = i;
		Queue_add(ptr, pcb2);
	}
	// Remove up to element 3.
	Queue_remove(ptr);
	Queue_remove(ptr);
	Queue_remove(ptr);
	// Should be element 3.
	printf("\nTest--Peek-> element[%d] pid[%d]", ptr->head, (*(ptr->pcbs+ptr->head))->PID);
	// Add some more elements to force a queue resize.
	for(i = 4; i < 9; i++) {
		pcb2 = (PcbPtr) malloc (sizeof(PcbStr));
		pcb2->PID = i;
		Queue_add(ptr, pcb2);
	}
	// Remove another for ish and giggles.
	Queue_remove(ptr);
	printf("\n\nWriting all info");
	for(i = 0, mod_i = ptr->head; i < ptr->count; i++, mod_i = (mod_i+1)%ptr->max) {
		printf("\nElement #%d is at index[%d]: pid=%d", i, mod_i, (*(ptr->pcbs+mod_i))->PID);
	}
	printf("\ncurrent count: %d", Queue_size(ptr));	

	Queue_destruct(ptr);

	return 0;
}
*/
