/*
 *  Process.h
 *  422project
 *
 *
 */


/**
 * Process Types: 0: User Interfacing Process (Keyboard)
 * 				  1: Compute Bound Process
 * 				  2: IO Bound Process
 * 				  3: Producer Process
 * 				  4: Consumer Process
 */

typedef struct process_str {
	int proc_type;       // code for process type, e.g. 0=compute, 1=i0, 2=keyboard, etc.
	int	no_steps;		// number of time steps before resetting to 0 - number of instructions
	int no_requests;	// number of requests that will be generated during the process run
	int* requests;		// an array of requests, each request (e.g. io service) is issued at a specific
						// time step. These are the synchronous events that result in traps being issued.
						// You can get fancy and make this an array of RequestTypeStr which contains the
						// step number when issued, and a request type (e.g. 0=io, 1=sync, etc.)
} ProcessStr;

typedef ProcessStr* ProcessPtr;
