#include <stdio.h>
#include <dfa.h>

// ===================================================================
// Declarations
// ===================================================================

// Setting up a DFA
DFA __dfa_create(transition_func transition, SET alphabet);

int cmp_character(void *a, void *b);
void print_node_value(RBNODE n);
void print_state_value(RBNODE n);

SET init_alphabet();

bool transition_label_is(RBNODE n, void *value);
TRANSITION find_transition(SET transitions, void *val);
STATE transition(STATE from, void *input);

bool state_label_is(RBNODE n, void *label);
STATE find_state(SET states, void *val);

// ===================================================================
// Public Functions
// ===================================================================
DFA dfa_create()
{
    return __dfa_create(&transition, init_alphabet());
}

DFA __dfa_create(transition_func transition, SET alphabet)
{
    DFA d = malloc(sizeof(struct dfa_t));

    if (d == NULL)
        return NULL;

    d->size = 0;
    d->accepting = set_create(alphabet->tree->cmp, &print_state_value);
    d->states = set_create(alphabet->tree->cmp, &print_state_value);

    d->delta = transition;
    d->U = alphabet;
    d->current = NULL;
    return d;
}

// ------------------------ STATE METHODS ----------------------------

STATE dfa_grab_state(DFA dfa, void*label)
{
    return find_state(dfa->states, label);
}

void dfa_add_state(DFA dfa, void *label, bool accepting) 
{
    STATE s = malloc(sizeof(struct state_t));

    if (s == NULL) return;

    s->label = label;

    // If this is the first state inserted into the set, 
    // it is our initial state
    if (set_size(dfa->states) == 0)
        dfa->current = s;

    // add the state into our states
    set_insert(dfa->states, s);
    
    // if its an accepting state, add our state into our accepting states.
    if (accepting)
        set_insert(dfa->accepting, s);
}

// ----------------------- TRANSITION METHODS ------------------------

TRANSITION dfa_grab_transition(DFA dfa, STATE from, void *on) {
    return find_transition(from->transitions, on);
}

bool dfa_add_transition(DFA dfa, void *from, void *to, void *character)
{
    TRANSITION t = malloc(sizeof(struct transition_t));
    
    if (t == NULL)
        return false;
    t->label = character;

    STATE from_state = dfa_grab_state(dfa, from);
    STATE to_state = dfa_grab_state(dfa, to);

    if (from_state == NULL || to_state == NULL)
        return false;

    t->next = to_state;

    return set_insert(from_state->transitions, t);
}

void dfa_transition(DFA dfa, void*input) 
{
    dfa->delta(dfa->current, input);
}

// ===================================================================
// Private Functions
// ===================================================================

int cmp_character(void *a, void *b)
{
    int c1 = (int)a;
    int c2 = (int)b;

    if (c1 > c2)
    {
        return 1;
    }
    else if (c1 == c2)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void print_node_value(RBNODE n)
{
    printf("%c ", (char)n->key);
}

void print_state_value(RBNODE n)
{
    STATE s = (STATE)n->key;
    printf("%c ", (char)s->label);
}

/**
 * For the sake of sake, we are assuming that all automata contain the input alphabet
 * of char's with values between 0 and 128.
 */
SET init_alphabet()
{
    SET alphabet = set_create(&cmp_character, &print_node_value);

    int i = 0;

    for (i = 0; i < 128; i++)
    {
        set_insert(alphabet, INT2VOIDP(i));
    }

    return alphabet;
}

bool transition_label_is(RBNODE n, void*value)
{
    TRANSITION t = (TRANSITION)n->key;
    if ((int)t->label == (int)value)
        return true;
    else
        return false;
}

TRANSITION find_transition(SET transitions, void*val) {
    RBTREE tree = transitions->tree;

    TRANSITION t = predicate_inorder(tree->root, transition_label_is, val)->key;
    return (TRANSITION)t;
}

STATE transition(STATE from, void*input)
{
    TRANSITION t = find_transition(from->transitions, input);
    if (t == NULL)
        return NULL;
    else
        return t->next;
}

bool state_label_is(RBNODE n, void*label)
{
    STATE s = (STATE)n->key;

    if ((char)s->label == (char)label)
        return true;
    else
        return false;
}

STATE find_state(SET states, void*label) 
{
    RBTREE tree = states->tree;

    STATE s = predicate_inorder(tree->root, state_label_is, label)->key;
    return (STATE)s;
}