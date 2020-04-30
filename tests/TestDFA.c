#include <narwhal.h>

#include <dfa.h>
#include <common.h>

TEST (DFA_CREATE) {
    DFA d = dfa_create();
    ASSERT(d != NULL);
}

TEST (DFA_INSERT_STATE) {
    DFA d = dfa_create();
    dfa_add_state(d, INT2VOIDP(1), false);
    ASSERT(dfa_grab_state(d, INT2VOIDP(1)) != NULL);
}

TEST (DFA_FIND_STATE) {
    DFA d = dfa_create();
    dfa_add_state(d, INT2VOIDP(1), false);
    dfa_add_state(d, INT2VOIDP(2), false);
    dfa_add_state(d, INT2VOIDP(3), false);
    dfa_add_state(d, INT2VOIDP(5), false);

    print_set(d->states);
    
    ASSERT(dfa_grab_state(d, INT2VOIDP(3)) != NULL);
    ASSERT(dfa_grab_state(d, INT2VOIDP(5)) != NULL);
    ASSERT(dfa_grab_state(d, INT2VOIDP(1)) != NULL);
}

TEST (DFA_ADD_TRANSITION) {
    DFA d = dfa_create();

    dfa_add_state(d, CHAR2VOIDP('a'), false);
    dfa_add_state(d, CHAR2VOIDP('b'), false);
    dfa_add_state(d, CHAR2VOIDP('c'), false);

    print_set(d->states);

    dfa_add_transition(d, CHAR2VOIDP('a'), CHAR2VOIDP('c'), CHAR2VOIDP('c'));

    STATE a = dfa_grab_state(d, CHAR2VOIDP('a'));
    TRANSITION t = dfa_grab_transition(d, a, CHAR2VOIDP('c'));

    ASSERT(t != NULL);
}