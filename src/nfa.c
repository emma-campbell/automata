#include <nfa.h>

#include <BitSet.h>
#include <IntHashSet.h>

#include <string.h>
#include <stdlib.h>

struct NFA {
	int size;
	Set **transitions;
	BitSet accepting;
	int curr;
};

NFA new_NFA(int nstates) 
{
	NFA nfa = malloc(sizeof(struct NFA));
	nfa->transitions = (Set**)malloc(sizeof(Set*));

	for (int i=0; i<nstates; i++)
	{
		nfa->transitions[i] = malloc(sizeof(Set));

		for (int j=0; j<128; j++)
		{
			*(*(nfa->transitions+i)+j) = new_Set(nstates);
		}
	}
	nfa->size = nstates;
	nfa->accepting = new_BitSet();
	nfa->curr = 0;
	return nfa;
}

void NFA_free(NFA nfa)
{
	BitSet_free(nfa->accepting);
	free(nfa);
}

int NFA_get_size(NFA nfa)
{
	return nfa->size;
}

Set NFA_get_transitions(NFA nfa, int state, char sym)
{
	return *(nfa->transitions[state]+sym);
}

void NFA_add_transition(NFA nfa, int src, char sym, int dst)
{
	Set_insert(*(nfa->transitions[src]+sym), dst);
}

void NFA_add_transition_str(NFA nfa, int src, char *str, int dst);

void NFA_add_transition_all(NFA nfa, int src, int dst)
{
	for (int i=0; i<128; i++)
	{
		if (Set_isEmpty(*(nfa->transitions[src]+i))) 
		{

			Set_insert(*(nfa->transitions[src]+i), dst);
		}
	}
}

void NFA_set_accepting(NFA nfa, int state)
{
	if (!BitSet_lookup(nfa->accepting, state))
	{
		BitSet_insert(nfa->accepting, state);
	}
}

bool NFA_get_accepting(NFA nfa, int state)
{
	return BitSet_lookup(nfa->accepting, state);
}

bool __execute(NFA nfa, char*input, int st)
{
	int src = st;

	if (strlen(input) == 1)
	{
		Set set = NFA_get_transitions(nfa, src, input[0]);
		if (Set_isEmpty(set)) return false;

		SetIterator it = Set_iterator(set);

		while (SetIterator_hasNext(it))
		{
			int cmp = SetIterator_next(it);
			if (NFA_get_accepting(nfa, cmp))
			{
				return true;
			}
		}
		return false;
	}

	Set set = NFA_get_transitions(nfa, src, input[0]);

	if (Set_isEmpty(set))
	{
		return false;
	}

	SetIterator it = Set_iterator(set);

	while (SetIterator_hasNext(it)) 
	{
		src = SetIterator_next(it);
		if (src < 32)
		{	
			if (__execute(nfa, input+1, src)) return true;
		}
	}
	return false;
}

bool NFA_execute(NFA nfa, char*input)
{
	return __execute(nfa, input, 0);
}
