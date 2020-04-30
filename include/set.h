/**
 * @file set.h
 * @author Emma Campbell
 * @date 04-18-2020
 * 
 * Set Data Structure
 * --------------------------------------------
 * Implementation choices:
 *  - No element may appear twice
 *  - Unordered set
 *  - Generic data type
 *  - Underlying Red-Black Tree
 * --------------------------------------------
 */

#ifndef _SET_H
#define _SET_H

#include <common.h>
#include <stdint.h>

#include <rbtree.h>

typedef void (*print_func)(RBNODE);

struct set_t
{
    int size;
    RBTREE tree;
    print_func print;
};

typedef struct set_t *SET;

// ======================================================================
// Creators && Destroyers
// ======================================================================

/**
 * @brief Create a new set
 * 
 * @param cmp function used to compare the elements of the set
 * @return SET empty set
 */
extern SET set_create(cmp_func_t cmp, void (*print) (RBNODE));

/**
 * @brief Destroy the memory allocated for the set
 * 
 * @param set Pointer to the set being destroyed
 */
extern void set_destroy(SET set);

// ======================================================================
// Insertion && Deletion
// ======================================================================

/**
 * @brief Insert into the set
 * 
 * @param set Pointer to the set
 * @param el element being inserted
 * @return {@code true} if insertion successful, {@code false} otherwise.
 */
extern bool set_insert(SET set, void *el);

/**
 * @brief Remove an element from the set
 * 
 * @param set Pointer to the set
 * @param el element being inserted
 * @return true if removal successful
 * @return false otherwise
 */
extern bool set_remove(SET set, void *el);

/**
 * @brief Find the element in the set
 * 
 * @param set Pointer to the set
 * @param el element we are trying to find
 * @return RBNODE pointer to the node within the set
 */
extern bool set_contains(SET set, void *el);

/**
 * @brief Returns a pointer to the node if it is found in the set
 * 
 * @param set Pointer to the set
 * @param el element we are trying to find.
 * @return RBNODE 
 */
extern RBNODE set_find(SET set, predicate p, void *val);

// ======================================================================
// Set Attributes
// ======================================================================

/**
 * @brief Return the size of the set
 * 
 * @param set Pointer to the set
 * @return int number of elements in the set
 */
extern int set_size(SET set);

/**
 * @brief print the elements of the set
 * 
 * @param set Pointer to the set
 */
extern void print_set(SET set);

// ======================================================================
// Set Operations
// ======================================================================

/**
 * @brief Returns the union of A and B, A u B.
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return SET union of A and B
 */
extern SET set_union(SET A, SET B);

/**
 * @brief Returns the difference of A and B, A - B.
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return SET difference of A and B
 */
extern SET set_difference(SET A, SET B);

/**
 * @brief Returns the intersection of A and B, A n B.
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return SET intersection of A and B.
 */
extern SET set_intersection(SET A, SET B);

/**
 * @brief Is set A equal to set B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is equal to B
 * @return false otherwise
 */
extern bool set_equals(SET A, SET B);

/**
 * @brief Is A disjoint to B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is disjoint to B
 * @return false otherwise
 */
extern bool set_disjoint(SET A, SET B);

/**
 * @brief Is A a subset of B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is a subset of B
 * @return false otherwise
 */
extern bool set_subset(SET A, SET B);

/**
 * @brief Is A a superset of B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is a superset of B
 * @return false otherwise
 */
extern bool set_superset(SET A, SET B);

/**
 * @brief Is A a strict subset of B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is a strict subset of B
 * @return false otherwise
 */
extern bool set_subset_strict(SET A, SET B);

/**
 * @brief Is A a strict superset of B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is a strict superset of B 
 * @return false otherwise.
 */
extern bool set_superset_strict(SET A, SET B);

// ======================================================================
// Iteration
// ======================================================================

/**
 * @brief Applies the given function to each element in the set
 * 
 * @param set Pointer to the set
 * @param func Pointer to the function
 */
extern void set_foreach(SET set, void(*func)(RBNODE));
#endif // _SET_H