/**
 * file: transformer.c
 * author: Emma Campbell
 */

// .-. . . .-. .   . . .-. .-. .-. 
//  |  |\| |   |   | | |  )|-  `-. 
// `-' ' ` `-' `-' `-' `-' `-' `-' 
#include <nfa.h>
#include <dfa.h>

#include <IntHashSet.h>
#include <LinkedList.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// .-. .-. .-. .-. . . .-. 
// |  )|-  |-   |  |\| |-  
// `-' `-' '   `-' ' ` `-' 

/**
 * @brief Return whether the list contains the given set
 * 
 * @param list pointer to the list
 * @param set pointer to the set
 * @return true if the set is in the list
 * @return false if the set is not in the list
 */
bool contains(LinkedList list, IntHashSet set)
{
    LinkedListIterator it = LinkedList_iterator(list);
    
    while (LinkedListIterator_hasNext(it)) 
    {
        if (IntHashSet_equals(LinkedListIterator_next(it), set))
        {
            free(it);
            return true;
        }
    }
 
    free(it);
    return false;
}

/**
 * @brief Insert the set into the list (Don't insert if already in the list)
 * 
 * @param list pointer to the list
 * @param set pointer to the set
 */
void insert(LinkedList list, IntHashSet set)
{
    if (!LinkedList_contains(list, set))
    {
        LinkedList_add_at_end(list, (void *)set);
    }
}

/**
 * @brief Return the indexState of the given set within the list
 * 
 * @param list pointer to the list
 * @param set pointer to the set
 * @return int the indexState of the set within the list
 */
int index(LinkedList list, IntHashSet set)
{
    LinkedListIterator it = LinkedList_iterator(list);
    int indexState = 0;

    while (LinkedListIterator_hasNext(it))
    {
        if (IntHashSet_equals(LinkedListIterator_next(it), set))
        {
	    free(it);
            return indexState;
        }
        indexState++;
    }
    free(it);
    return indexState;
}

/**
 * @brief Return the size of the LinkedList
 * 
 * @param list pointer to the list
 * @return int size of the list
 */
int size(LinkedList list)
{
    LinkedListIterator it = LinkedList_iterator(list);
    int size = 0;

    while (LinkedListIterator_hasNext(it))
    {
        LinkedListIterator_next(it);
        size++;
    }
    free(it);
    return size;
}

/**
 * @brief Convert the NFA into new DFA
 * 
 * @param nfa pointer to the NFA
 * @return DFA Pointer to the converted DFA
 */
DFA NFA_to_DFA(NFA nfa) 
{

    // Theoretically, the maximum number of states in a DFA after
    // conversion from a NFA should be numNFAStates^2
    DFA dfa = new_DFA((int)pow(2, NFA_get_size(nfa)));

    LinkedList finalStates = new_LinkedList();
    LinkedList sets = new_LinkedList();

    // pointers to the states we are creating (set of states)
    IntHashSet state = new_IntHashSet(DFA_get_size(dfa));
    IntHashSet nextState = new_IntHashSet(DFA_get_size(dfa));
    IntHashSet_insert(state, 0);

    LinkedList_add_at_front(finalStates, state);
    LinkedList_add_at_front(sets, state);

    int currState = 0;
    int indexState = 0;
    int dst = 0;

    IntHashSet tmp = NULL;

    while (!LinkedList_isEmpty(sets))
    {
        IntHashSet unionSet = new_IntHashSet(128);

        tmp = LinkedList_pop(sets);

        state = tmp;
        IntHashSetIterator it = IntHashSet_iterator(state);

        while (IntHashSetIterator_hasNext(it))
        {
            currState = IntHashSetIterator_next(it);
            for (int i = 0; i < 128; i++) {
                nextState = NFA_get_transitions(nfa, currState, (char)i);
                
                if (!IntHashSet_equals(unionSet, nextState))
                {
                    IntHashSet_union(unionSet, nextState);
                }
            }
        }

	free(it);

        for (int i = 0; i < 128; i++) 
        {
            if (!contains(finalStates, unionSet))
            {
                LinkedList_add_at_end(finalStates, unionSet);
                LinkedList_add_at_end(sets, unionSet);
            }

            indexState = index(finalStates, state);
            dst = index(finalStates, unionSet);

            DFA_set_transition(dfa, indexState, (char)i, dst);
        }
    }

    LinkedListIterator it_accepting = LinkedList_iterator(finalStates);

    while (LinkedListIterator_hasNext(it_accepting))
    {
        IntHashSet currSet = LinkedListIterator_next(it_accepting);
        IntHashSetIterator itSet = IntHashSet_iterator(currSet);

        while (IntHashSetIterator_hasNext(itSet))
        {
            int st = IntHashSetIterator_next(itSet);
            if (NFA_get_accepting(nfa, st))
            {
                DFA_set_accepting(dfa, index(finalStates, currSet));
            }
        }
    	free(itSet);
    }

    free(it_accepting);

    return dfa;
}
