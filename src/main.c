#include <dfa.h>

#include <stdio.h>
#include <string.h>

DFA make_first_dfa()
{
	DFA dfa = new_DFA(6);
	
	DFA_set_transition(dfa, 0, 'c', 1);
	DFA_set_transition(dfa, 1, 's', 2);
	DFA_set_transition(dfa, 2, 'c', 3);
	DFA_set_transition(dfa, 3, '1', 4);
	DFA_set_transition(dfa, 4, '7', 5);
	DFA_set_transition(dfa, 5, '3', 6);

	DFA_set_accepting(dfa, 6);
	return dfa;
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

int main(void)
{
	DFA d1;

	printf("Project 1 by Emma Campbell\n");
	printf("Testing DFA the recognizes exactly the string \"csc173\"...\n");

	d1 = make_first_dfa();
	test_dfa(d1);
}
