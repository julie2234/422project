/*
 *  Process.c
 *  422project
 *
 *
 */

#include "Process.h"
#include <stdio.h>

ProcessPtr ProcessContructor()
{
	ProcessPtr temp_process = (ProcessPtr) malloc(sizeOf(ProcessStr));

	return temp_process;
}
