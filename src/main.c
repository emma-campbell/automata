/**
 * Entry point into application
 * 
 * @file main.c
 * @date 04/18/2020
 */

#include <stdio.h>
#include <dfa.h>

int main(void)
{

	DFA d = dfa_create();
	
	dfa_add_state(d, (void*)'a', false);
	dfa_add_state(d, (void*)'b', false);
	dfa_add_state(d, (void*)'c', false);
	
	print_set(d->states);

	STATE c = dfa_grab_state(d, (void *)'c');
	STATE a = dfa_grab_state(d, (void*)'a');


	if ((char)a->label == 'a')
		printf("\nGrab state 'a': SUCCESS\n");
	else {
		printf("\nGrab state 'a': FAIL\n");
		printf("Got: %c", (char)a->label);
	}

	if ((char)c->label == 'c')
		printf("Grab state 'c': SUCCESS\n");
	else
		printf("Grab state 'c': FAIL\n");

	return 0;
}
