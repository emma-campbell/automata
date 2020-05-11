#include <dfa.h>
#include <nfa.h>

#include <stdio.h>
#include <string.h>

DFA make_first_dfa()
{
	DFA dfa = new_DFA(7);
	
	DFA_set_transition(dfa, 0, 'c', 1);
	DFA_set_transition(dfa, 1, 's', 2);
	DFA_set_transition(dfa, 2, 'c', 3);
	DFA_set_transition(dfa, 3, '1', 4);
	DFA_set_transition(dfa, 4, '7', 5);
	DFA_set_transition(dfa, 5, '3', 6);

	DFA_set_accepting(dfa, 6);
	return dfa;
}

DFA make_second_dfa()
{
	/**
	 * Any string that starts with CAT
	 */
	DFA dfa = new_DFA(4);

	DFA_set_transition(dfa, 0, 'c', 1);
	DFA_set_transition(dfa, 1, 'a', 2);
	DFA_set_transition(dfa, 2, 't', 3);
	DFA_set_transition_all(dfa, 3, 3);

	DFA_set_accepting(dfa, 3);
	return dfa;
}


DFA make_third_dfa()
{
	/**
	 * Accepts an even number of 1's
	 */
	DFA dfa = new_DFA(2);
	
	DFA_set_transition(dfa, 0, '0', 1);
	DFA_set_transition(dfa, 1, '1', 1);
	DFA_set_transition(dfa, 1, '0', 0);
	DFA_set_transition(dfa, 0, '1', 0);

	DFA_set_accepting(dfa, 0);
	return dfa;
}


DFA make_fourth_dfa()
{
	DFA dfa = new_DFA(4);

	DFA_set_transition(dfa, 0, '0', 1);
	DFA_set_transition(dfa, 1, '0', 0);

	DFA_set_transition(dfa, 1, '1', 2);
	DFA_set_transition(dfa, 2, '1', 1);

	DFA_set_transition(dfa, 2, '0', 3);
	DFA_set_transition(dfa, 3, '0', 2);

	DFA_set_transition(dfa, 3, '1', 0);
	DFA_set_transition(dfa, 0, '1', 3);

	DFA_set_accepting(dfa, 0);
	return dfa;
}

NFA make_first_nfa()
{
	NFA nfa = new_NFA(5);
	
	NFA_add_transition(nfa, 0, 'c', 0);
    	NFA_add_transition(nfa, 0, 'c', 1);
        NFA_add_transition_all(nfa, 0, 0);
    	NFA_add_transition(nfa, 1, 'o', 2);
    	NFA_add_transition(nfa, 2, 'd', 3);
    	NFA_add_transition(nfa, 3, 'e', 4);
    
	NFA_set_accepting(nfa, 4);
	return nfa;
}

void test_dfa(DFA d)
{
	char input[256];

	do
	{
		printf("Enter an input (\"quit\" to quit): ");
		scanf("%s[^\n]", input);

		if (!strcmp(input, "quit"))
		{
			break;
		}

		bool res = DFA_execute(d, input);

		if (res)
		{
			printf("Result for \"%s\": true\n", input);
		}
		else 
		{
			printf("Result for \"%s\": false\n", input);
		}

	} while (strcmp(input, "quit"));

	DFA_free(d);
}

void test_nfa(NFA n)
{
	char input[256];

	do
	{
		printf("Enter an input (\"quit\" to quit): ");
		scanf("%s[^\n]", input);

		if (!strcmp(input, "quit"))
		{
			break;
		}

		bool res = NFA_execute(n, input);

		if (res)
		{
			printf("Result for \"%s\": true\n", input);
		}
		else 
		{
			printf("Result for \"%s\": false\n", input);
		}

	} while (strcmp(input, "quit"));

	NFA_free(n);
}


int main(void)
{
	DFA d1, d2, d3, d4;
	NFA n1;

	printf("Project 1 by Emma Campbell\n");
	printf("Testing DFA the recognizes exactly the string \"csc173\"...\n");

	d1 = make_first_dfa();
	test_dfa(d1);

	printf("\n\nTesting DFA that recognizes the string that starts with \"cat\"...\n");

	d2 = make_second_dfa();
	test_dfa(d2);

	printf("\n\nTesting DFA that recognizes the string that has a even number of 0's...\n");

	d3 = make_third_dfa();
	test_dfa(d3);

	printf("\n\nTesting DFA that recognizes the string that has an even number of 0's and 1's...\n");

	d4 = make_fourth_dfa();
	test_dfa(d4);
	

	printf("\n\nTesting NFA that recognizes strings ending in \"code\"...\n");
	n1 = make_first_nfa();
	test_nfa(n1);
	

}
