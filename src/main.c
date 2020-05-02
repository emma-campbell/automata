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
	printf("\n");

	char from = 'a';
	char to = 'c';
	char on = 'g';

	dfa_add_transition(d, INT2VOIDP(from), INT2VOIDP(to), INT2VOIDP(on));
	
	return 0;
}
