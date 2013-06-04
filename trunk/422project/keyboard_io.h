/*
 * keyboard_io.h
 *
 *  Created on: Jun 1, 2013
 *      Author: tyler
 */

#ifndef KEYBOARD_IO_H_
#define KEYBOARD_IO_H_

#include <stdio.h>
#include <pthread.h>
#include "controller.h"
#include "CPU.h"

void *keyboardListener(void* parameter);
void startKeyboardListener(int process_id);
void keyPressInterrupt(char pressedKey);

#endif /* KEYBOARD_IO_H_ */
