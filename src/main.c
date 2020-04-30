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

	char label = 'a';
	STATE A = dfa_grab_state(d, INT2VOIDP(label));

	printf("State A:\n");
	printf("%c ", (char)A->label);
	printf("\n");

	return 0;
}
