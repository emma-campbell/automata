/**
 * @file dfa.c
 * @date 05/10/2020
 *
 * © Emma Campbell 2020
 */

#include <dfa.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <BitSet.h>
#include <IntHashSet.h>

struct DFA{
	int size;
	int**transitions;
	BitSet accepting;
};

DFA new_DFA(int nstates)
{
	DFA dfa = malloc(sizeof(struct DFA));
	assert(dfa != NULL);

	dfa->size = nstates;
	
	dfa->accepting = new_BitSet(nstates);
	dfa->transitions = malloc(nstates * sizeof(int*));

	for (int i=0; i<nstates; i++)
	{
		dfa->transitions[i] = malloc(128 *sizeof(int*));
		for (int j=0; j<128;j++)
		{
			dfa->transitions[i][j] = -1;
		}
	}

	return dfa;
}


void DFA_free(DFA dfa)
{
	BitSet_free(dfa->accepting);

	for (int i=0; i<dfa->size; i++)
	{
		free(dfa->transitions[i]);
	}
	free(dfa->transitions);
	free(dfa);
}


int DFA_get_size(DFA dfa)
{
	return dfa->size;
}

int DFA_get_transition(DFA dfa, int src, char sym)
{
	return dfa->transitions[src][(int)sym];
}

void DFA_set_transition(DFA dfa, int src, char sym, int dst)
{
	dfa->transitions[src][(int)sym] = dst;
}

void dfa_set_transition_str(DFA dfa, int src, char*str, int dst)
{
	char *p;

	p = str;

	while (*p != '\0')
	{
		dfa->transitions[src][(int)*p++] = dst;
	}
}

void DFA_set_transition_all(DFA dfa, int src, int dst)
{
	for (int i=0; i<128; i++)
	{
		dfa->transitions[src][i] = dst;
	}
}

void DFA_set_accepting(DFA dfa, int state)
{
	if (!BitSet_lookup(dfa->accepting, state))
	{
		BitSet_insert(dfa->accepting, state);
	}
}

bool DFA_get_accepting(DFA dfa, int state)
{
	return BitSet_lookup(dfa->accepting, state);
}

bool DFA_execute(DFA dfa, char*input)
{
	int src = 0;

	int i = 0;

	while (input[i] != '\0')
	{
		src = DFA_get_transition(dfa, src, input[i++]);
		if (src == -1) return false;
	}

	return DFA_get_accepting(dfa, src);
}

	

