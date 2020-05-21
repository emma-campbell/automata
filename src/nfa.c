#include <nfa.h>

#include <BitSet.h>
#include <IntHashSet.h>

#include <string.h>
#include <stdlib.h>

struct NFA {
	int size;
	IntHashSet**transitions;
	BitSet accepting;
	int curr;
};

NFA new_NFA(int nstates) 
{
	NFA nfa = NULL;
	nfa = malloc(sizeof(struct NFA));

	if (nfa == NULL) return NULL;

	nfa->transitions = malloc(nstates*sizeof(IntHashSet*));

	for (int i=0; i<nstates; i++)
	{
		nfa->transitions[i] = malloc(128*sizeof(IntHashSet));

		for (int j=0; j<128; j++)
		{
			*(*(nfa->transitions+i)+j) = new_IntHashSet(nstates);
		}
	}
	nfa->size = nstates;
	nfa->accepting = new_BitSet();
	nfa->curr = 0;
	return nfa;
}

void NFA_free(NFA nfa)
{
	for (int i=0; i<nfa->size; i++)
	{
		for (int j=0; j<128; j++)
		{
			IntHashSet_free(*(*(nfa->transitions+i)+j));
		}
		free(nfa->transitions[i]);
	}
	free(nfa->transitions);
	BitSet_free(nfa->accepting);
	free(nfa);
}

int NFA_get_size(NFA nfa)
{
	return nfa->size;
}

IntHashSet NFA_get_transitions(NFA nfa, int state, char sym)
{
	return *(nfa->transitions[state]+sym);
}

void NFA_add_transition(NFA nfa, int src, char sym, int dst)
{
	IntHashSet_insert(*(nfa->transitions[src]+sym), dst);
}

void NFA_add_transition_str(NFA nfa, int src, char *str, int dst);

void NFA_add_transition_all(NFA nfa, int src, int dst)
{
	for (int i=0; i<128; i++)
	{
		if (Set_isEmpty(*(nfa->transitions[src]+i))) 
		{

			IntHashSet_insert(*(nfa->transitions[src]+i), dst);
		}
	}
}

void NFA_add_transition_all_except(NFA nfa, int src, int dst, char except) 
{
	for (int i=0; i<128; i++)
	{
		if (i != except)
		{
			if (Set_isEmpty(*(nfa->transitions[src]+i)))
			{
				IntHashSet_insert(*(nfa->transitions[src]+i), dst);
			}
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
		IntHashSet set = NFA_get_transitions(nfa, src, input[0]);
		if (IntHashSet_isEmpty(set)) return false;

		IntHashSetIterator it = IntHashSet_iterator(set);

		while (IntHashSetIterator_hasNext(it))
		{
			int cmp = IntHashSetIterator_next(it);
			if (NFA_get_accepting(nfa, cmp))
			{
				return true;
			}
		}
		return false;
	}

	IntHashSet set = NFA_get_transitions(nfa, src, input[0]);

	if (IntHashSet_isEmpty(set))
	{
		return false;
	}

	IntHashSetIterator it = IntHashSet_iterator(set);

	while (IntHashSetIterator_hasNext(it)) 
	{
		src = IntHashSetIterator_next(it);
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
