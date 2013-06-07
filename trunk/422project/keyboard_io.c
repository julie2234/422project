/*
 * KeyboardIO.c
 *	GPOS Scheduler Simulation
 *  Team 8: Simrell, Trottier, Morris, Impola
 *	TCSS 422, Spring 2013
 */

#include "keyboard_io.h"

int continueListening = 1;
int process_waiting;
char key_pressed;

void *keyboardListener(void* parameter)
{
	char input_character;
	while(continueListening)
	{
		input_character = getchar();
		getchar(); // throw away enter key
		continueListening = 0;
		key_pressed = input_character;
		keyPressInterrupt(input_character);
	}

	continueListening = 1; //turn back on the ability to take in characters.
	return 0;
}

void startKeyboardListener(int process_id)
{
	//printf("Starting Keyboard Listener");
	pthread_t keyboard_thread;
	process_waiting = process_id;
	pthread_create(&keyboard_thread, NULL, keyboardListener, NULL);
}

void keyPressInterrupt(char pressedKey)
{
	setInterrupt(1, process_waiting);
}

char getKeyPress()
{
	return key_pressed;
}

//void main(void)
//{
//	startKeyboardListener();
//
//}
