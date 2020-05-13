#include <nfa.h>
#include <dfa.h>

#include <IntHashSet.h>
#include <LinkedList.h>

DFA NFA_to_DFA(NFA nfa)
{
	Set s = new_Set();
	LinkedList* state_labels = new_LinkedList();

	Set_insert(s, 0);
	LinkedList_add_at_front(state_labels, s);

	int list_index = -1;
	int list_size = 1;

	Set it_set;
	Set s2;

	do
	{
		list_size = LinkedList_size(state_labels);
		list_index++;

		it_set = LinkedList_elementAt(state_labels, list_index);
		for (int i=0; i<128; i++)
		{
			SetIterator it = Set_iterator();
			s2 = new_Set();

			while (SetIterator_hasNext(it))
			{
				Set_union(set2, NFA_get_transitions(nfa, SetIterator_next(it), i));
			}
			free(it);

			if ((!LinkedList_contains(state_labels, s2)) &&
					(!Set_isEmpty(s2))) 
			{
				LinkedList_add_at_end(state_labels, s2);
			}
		}
	} while ((LinkedList_size(state_labels) != list_size) ||
			(list_index + 1) != LinkedList_size(state_labels));

	
	// Now, lets form the DFA
	int dfa_numstates = LinkedList_size(state_labels);
	DFA dfa = new_DFA(dfa_numstates);

	for (int i=0; i<DFA_get_size(dfa); i++)
	{
		Set s4 = LinkedList_elementAt(state_labels, i);
		for (int j=0; j<128; j++)
		{
			SetIterator it = Set_iterator(s4);
			Set s5 = new_Set();

			while (SetIterator_hasNext(it))
			{
				Set_union(s5, NFA_get_transitions(nfa, SetIterator_next(it), j));
			}
			int curr = 0;

			while (!(Set_equals(s5, LinkedList_elementAt(state_labels, curr))))
			{
				curr++;
			}

			DFA_set_transition(dfa, i, j, curr);
			Set_free(s5);
			free(it);

		}
	}

	int dfa_state_index = 0;
	LinkedListIterator* accept_iterator = LinkedList_iterator(state_labels);

	while (LinkedListIterator_hasNext(accept_iterator))
	{
		Set set = LinkedListIterator_next(accept_iterator);
		SetIterator set_it = Set_iterator(set);

		while (SetIterator_hasNext(set_it))
		{
			int curr = SetIterator_next(set_it);
			if (NFA_get_accepting(nfa, curr))
			{
				DFA_set_accepting(dfa, dfa_state_index);
			}
		}
		free(set_it);
		dfa_state_index++;
	}
	free(accept_iterator);
	LinkedList_free(state_labels, true);
	return dfa;
}

	
