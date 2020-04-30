/**
 * @brief Client-facing header file for DFA
 */
#ifndef _DFA_h
#define _DFA_h

#define MAX_STATES 100
#define MAX_TRANSITIONS 50

#include <set.h>

/**
 * DETERMINISTIC FINITE AUTOMATA
 * The characteristics of a DFA are as follows:
 *  - Finite set of states
 *  - Finite input alphabet
 *  - Transition function
 *  - Set of accepting states
 */

struct state_t
{
  SET transitions; // set of transitions out of the state
  bool lambda;     // transition occurs with any input
  void *label;     // label of the state
};

typedef struct state_t *STATE;

struct transition_t
{
  void *label; // input that transition occurs on
  STATE next;  // the next state that we transit into
};

typedef struct transition_t *TRANSITION;

typedef STATE (*transition_func)(STATE s, void *input);

struct dfa_t
{
  int size; // number of states

  SET states;            // finite set of states
  SET accepting;         // set of accepting
  SET U;                 // 'universal' (alphabet) set
  transition_func delta; // transition function to next state.

  STATE current; // the current state of the dfa machine
};

typedef struct dfa_t *DFA;

// =======================================================================================
// DFA API -- Client Facing
// =======================================================================================

/**
 * @brief Create a new DFA structure
 *
 * @return DFA structure -- completely initialized
 */
extern DFA dfa_create();

// =======================================================================================
// STATE METHODS
// =======================================================================================

/**
 * @brief Get a state from its label
 * 
 * @param dfa Pointer to the DFA
 * @param label Label on the state (STATE 'a')
 * @return the state, if found, NULL otherwise.
 */
extern STATE dfa_grab_state(DFA dfa, void *label);

/**
 * @brief Make a new state with the given attributes
 *
 * @param label Label on the state (i.e. STATE 'a').
 * @param accepting Boolean indicating whether the state is accepting or not.
 */
extern void dfa_add_state(DFA dfa, void *label, bool accepting);

// ========================================================================================
// TRANSITION METHODS
// ========================================================================================

/**
 * @brief Grabs the transition structure from a the dfa
 * 
 * @param dfa 
 * @param on 
 * @return STATE 
 */
extern TRANSITION dfa_grab_transition(DFA dfa, STATE from, void *on);

/**
 * @brief Create a new transition
 *
 * @param from The state where the transition starts
 * @param to The state where the transition ends
 */
extern bool dfa_add_transition(DFA dfa, void *from, void *to, void *character);

/**
 * @brief Follow the transition given the input
 *
 * @param input Value that triggers the transition (will be on the label of the transition)
 */
extern void dfa_transition(DFA dfa, void *input);

#endif //_DFA_h
