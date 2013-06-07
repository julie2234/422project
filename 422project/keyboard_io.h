/*
 * keyboard_io.h
 *	GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#ifndef KEYBOARD_IO_H_
#define KEYBOARD_IO_H_

#include <stdio.h>
#include <pthread.h>
#include "controller.h"

void *keyboardListener(void* parameter);
void startKeyboardListener(int process_id);
void keyPressInterrupt(char pressedKey);

#endif /* KEYBOARD_IO_H_ */
