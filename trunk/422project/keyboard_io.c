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

void *keyboardListener(void* parameter)
{
	char input_character;
	while(continueListening)
	{
		input_character = getchar();
        if(input_character == '.')
        {
            return 0;
        }
        if(input_character != 10) //ascii for '.'
        {
        	keyPressInterrupt(input_character);
        }
	}

	return 0;
}

void startKeyboardListener(void)
{
	pthread_t keyboard_thread;
	pthread_create(&keyboard_thread, NULL, keyboardListener, NULL);
}

//void main(void)
//{
//	startKeyboardListener();
//
//}
