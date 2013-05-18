/*
 * PCB.c
 *
 *  Created on: May 18, 2013
 */

PCBPtr PCBConstructor(int sent_in_PID, ProcessPtr process)
{
	PCBPtr temp_PCB = (PCBPtr) malloc(sizeOf(PCBStr));
	//Create process

	temp_PCB->pid = sent_in_PID;
	return temp_PCB;
}


