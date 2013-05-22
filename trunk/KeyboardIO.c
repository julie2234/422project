/*
 * KeyboardIO.c
 *
 *  Created on: May 22, 2013
 *      Author: tyler
 */

#include <stdio.h>
#include <pthread.h>

int continueListening = 1;

void *keyboardListener(void)
{
	char input_character;
	while(continueListening)
	{
		input_character = getchar();
        if(input_character == '.')
        {
            pthread_exit(NULL);
        }
        if(input_character != 10)
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
    pthread_exit(NULL);
}

//void main(void)
//{
//	startKeyboardListener();
//
//}
