/*
 * KeyboardIO.c
 *
 *  Created on: May 22, 2013
 *      Author: tyler
 */

#include <stdio.h>
#include <pthread.h>
#include "keyboard_io.h"
#include "controller.h"

int continueListening = 1;
int process_waiting;

void *keyboardListener(void* parameter)
{
	char input_character;
	while(continueListening)
	{
		input_character = getchar();
		continueListening = 1;
		keyPressInterrupt(input_character);
	}

	return 0;
}

void startKeyboardListener(int process_id)
{
	printf("Starting Keyboard Listener");
	pthread_t keyboard_thread;
	process_waiting = process_id;
	pthread_create(&keyboard_thread, NULL, keyboardListener, NULL);
}

void keyPressInterrupt(char pressedKey)
{
	printf("You pressed %c\n", pressedKey);
	printf("Which is %d in ascii\n", pressedKey);
	printf("Process %d", process_waiting);
}

//void main(void)
//{
//	startKeyboardListener();
//
//}
