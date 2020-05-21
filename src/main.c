#include <dfa.h>
#include <nfa.h>
#include <transformer.h>

#include <stdio.h>
#include <string.h>

DFA make_first_dfa()
{
	/**
	 * Exactly the string "csc173"
	 */
	DFA dfa = NULL;

	dfa = new_DFA(7);

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
	DFA dfa = NULL;
	dfa = new_DFA(4);

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
	 * Accepts an even number of 0's
	 */
	DFA dfa = NULL;
	dfa = new_DFA(2);

	DFA_set_transition(dfa, 0, '0', 1);
	DFA_set_transition(dfa, 1, '1', 1);
	DFA_set_transition(dfa, 1, '0', 0);
	DFA_set_transition(dfa, 0, '1', 0);

	DFA_set_accepting(dfa, 0);
	return dfa;
}

DFA make_fourth_dfa()
{
	/**
	 * Accepts an even number of both 0's and 1's
	 */
	DFA dfa = NULL;
	dfa = new_DFA(4);

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
	/**
	 * Accepts strings ending in code
	 */
	NFA nfa = NULL;
	nfa = new_NFA(5);

	NFA_add_transition(nfa, 0, 'c', 0);
	NFA_add_transition(nfa, 0, 'c', 1);
	NFA_add_transition_all(nfa, 0, 0);
	NFA_add_transition(nfa, 1, 'o', 2);
	NFA_add_transition(nfa, 2, 'd', 3);
	NFA_add_transition(nfa, 3, 'e', 4);

	NFA_set_accepting(nfa, 4);
	return nfa;
}

NFA make_second_nfa()
{

	/**
	 * Accepts strings containing code
	 */
	NFA nfa = NULL;
	nfa = new_NFA(5);

	NFA_add_transition(nfa, 0, 'c', 0);
	NFA_add_transition(nfa, 0, 'c', 1);
	NFA_add_transition_all(nfa, 0, 0);
	NFA_add_transition(nfa, 1, 'o', 2);
	NFA_add_transition(nfa, 2, 'd', 3);
	NFA_add_transition(nfa, 3, 'e', 4);
	NFA_add_transition_all(nfa, 4, 4);

	NFA_set_accepting(nfa, 4);
	return nfa;
}

NFA make_third_nfa()
{
	/**
	 * Accepts strings that AREN'T partial anagrams of washington
	 */
	NFA nfa = new_NFA(20);
	NFA_add_transition_all(nfa, 0, 0);
	NFA_add_transition_all(nfa, 1, 1);
	NFA_add_transition_all(nfa, 2, 2);
	NFA_add_transition_all(nfa, 3, 3);
	NFA_add_transition_all(nfa, 4, 4);
	NFA_add_transition_all(nfa, 5, 5);
	NFA_add_transition_all(nfa, 6, 6);
	NFA_add_transition_all(nfa, 7, 7);
	NFA_add_transition_all(nfa, 8, 8);
	NFA_add_transition_all(nfa, 9, 9);
	NFA_add_transition_all(nfa, 10, 10);

	NFA_add_transition(nfa, 0, 'a', 1);

	NFA_add_transition(nfa, 1, 'a', 10);

	NFA_add_transition(nfa, 0, 'g', 2);
	NFA_add_transition(nfa, 2, 'g', 10);
	NFA_add_transition(nfa, 0, 'h', 3);
	NFA_add_transition(nfa, 3, 'h', 10);
	NFA_add_transition(nfa, 0, 'i', 4);
	NFA_add_transition(nfa, 4, 'i', 10);
	NFA_add_transition(nfa, 0, 'o', 5);
	NFA_add_transition(nfa, 5, 'o', 10);
	NFA_add_transition(nfa, 0, 's', 6);
	NFA_add_transition(nfa, 6, 's', 10);
	NFA_add_transition(nfa, 0, 't', 7);
	NFA_add_transition(nfa, 7, 't', 10);
	NFA_add_transition(nfa, 0, 'n', 8);
	NFA_add_transition(nfa, 8, 'n', 9);
	NFA_add_transition(nfa, 9, 'n', 10);
	NFA_add_transition(nfa, 0, 'w', 11);
	NFA_add_transition(nfa, 11, 'w', 10);
	NFA_set_accepting(nfa, 10);
	return nfa;
}

/**
 * @brief Test the DFA against the given input
 * 
 * @param d pointer to the dfa
 */
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

/**
 * @brief Test the NFA against the given input
 * 
 * @param n Pointer to the nfa
 */
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

/**
 * @brief Tests the washington NFA, since it accepts strings that aren't	
 * 		  partial anagrams, so just switches the print statement.
 * 
 * @param n Pointer to the NFA
 */
void test_washington(NFA n)
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
			printf("\"%s\" is not a partial anagram of \"washington\"\n", input);
		}
		else
		{
			printf("\"%s\" is a partial anagram of \"washington\"\n", input);
		}

	} while (strcmp(input, "quit"));

	NFA_free(n);
}

int main(void)
{
	DFA d1, d2, d3, d4;
	NFA n1, n2, n3;

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

	printf("\n\nTesting NFA that recognizes strings containing \"code\"...\n");

	n2 = make_second_nfa();
	test_nfa(n2);

	printf("\n\nTesting NFA that recognizes strings that are partial anagrams of 'washington'...\n");
	n3 = make_third_nfa();
	test_washington(n3);

	printf("\n\nNow converting NFA that recognizes strings ending in \"code\"...\n");
	NFA code = make_first_nfa();
	printf("The NFA has %d states, ", NFA_get_size(code));
	DFA converted = NFA_to_DFA(code);
	printf("It has %d states once converted.", DFA_get_size(converted));

	printf("\n\nNow converting NFA that recognizes strings containing \"code\"...\n");
	NFA end_in_code = make_second_nfa();
	printf("The NFA has %d states, ", NFA_get_size(end_in_code));
	DFA converted_code = NFA_to_DFA(end_in_code);
	printf("It has %d states once converted.", DFA_get_size(converted_code));

	printf("\n\nNow converting NFA that recognizes partial anagrams of \"washington\"...\n");
	NFA washington = make_third_nfa();
	printf("The NFA has %d states, ", NFA_get_size(washington));
	DFA washingtonDFA = NFA_to_DFA(washington);
	printf("It has %d states once converted.", DFA_get_size(washingtonDFA));
}
