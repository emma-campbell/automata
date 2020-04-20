
#include <set.h>
#include <stdio.h>

// ======================================================================
// Creators && Destroyers
// ======================================================================

/**
 * @brief Create a new set
 * 
 * @param cmp function used to compare the elements of the set
 * @return SET empty set
 */
SET set_create(cmp_func_t cmp, void(*print)(RBNODE)) {
    SET s = malloc(sizeof(struct set_t));
    
    if (s == NULL)
        return NULL;
    
    s->tree = rb_create(cmp);
    s->size = 0;
    s->print = print;

    return s;
}

/**
 * @brief Destroy the memory allocated for the set
 * 
 * @param set Pointer to the set being destroyed
 */
void set_destroy(SET set) {
    rb_destroy(set->tree);
    set->size = 0;
    free(set);
}

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
bool set_insert(SET set, void *el) {
    int res = rb_insert(set->tree, el);
    set->size++;
    return res;
}

/**
 * @brief Remove an element from the set
 * 
 * @param set Pointer to the set
 * @param el element being inserted
 * @return true if removal successful
 * @return false otherwise
 */
bool set_remove(SET set, void *el) {
    int res = (rb_remove(set->tree, el) != NULL);
    set->size--;
    return res;
}

/**
 * @brief Find the element in the set
 * 
 * @param set Pointer to the set
 * @param el element we are trying to find
 * @return RBNODE pointer to the node within the set
 */
bool set_contains(SET set, void *el) {
    return (rb_find(set->tree, el) != NULL);
}

// ======================================================================
// Set Attributes
// ======================================================================

/**
 * @brief Return the size of the set
 * 
 * @param set Pointer to the set
 * @return int number of elements in the set
 */
int set_size(SET set) {
    return set->size;
}

/**
 * @brief print the elements of the set
 * 
 * @param set Pointer to the set
 */
void print_set(SET set) {
    printf("( ");
    print_tree(set->tree, set->print);
    printf(")");
}

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
SET set_union(SET A, SET B) {
    SET u = set_create(A->tree->cmp, A->print);
    u->tree = rb_union(A->tree, B->tree);
    u->size = rb_size(u->tree);
    return u;
}

/**
 * @brief Returns the difference of A and B, A - B.
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return SET difference of A and B
 */
SET set_difference(SET A, SET B) {
    SET u = set_create(A->tree->cmp, A->print);
    u->tree = rb_difference(A->tree, B->tree);
    u->size = rb_size(u->tree);
    return u;
}

/**
 * @brief Returns the intersection of A and B, A n B.
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return SET intersection of A and B.
 */
SET set_intersection(SET A, SET B) {
    SET u = set_create(A->tree->cmp, A->print);
    u->tree = rb_intersection(A->tree, B->tree);
    u->size = rb_size(u->tree);
    return u;
}

/**
 * @brief Is set A equal to set B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is equal to B
 * @return false otherwise
 */
bool set_equals(SET A, SET B) {
    return rb_equals(A->tree, B->tree);
}

/**
 * @brief Is A disjoint to B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is disjoint to B
 * @return false otherwise
 */
bool set_disjoint(SET A, SET B) {
    return rb_is_disjoint(A->tree, B->tree);
}

/**
 * @brief Is A a subset of B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is a subset of B
 * @return false otherwise
 */
bool set_subset(SET A, SET B) {
    return rb_is_subset(A->tree, B->tree);
}

/**
 * @brief Is A a superset of B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is a superset of B
 * @return false otherwise
 */
bool set_superset(SET A, SET B) {
    return rb_is_superset(A->tree, B->tree);
}

/**
 * @brief Is A a strict subset of B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is a strict subset of B
 * @return false otherwise
 */
bool set_subset_strict(SET A, SET B) {
    return rb_is_subset_strict(A->tree, B->tree);
}

/**
 * @brief Is A a strict superset of B?
 * 
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @return true if A is a strict superset of B 
 * @return false otherwise.
 */
bool set_superset_strict(SET A, SET B) {
    return rb_is_superset_strict(A->tree, B->tree);
}

// ======================================================================
// Iteration
// ======================================================================

/**
 * @brief Applies the given function to each element in the set
 * 
 * @param set Pointer to the set
 * @param func Pointer to the function
 */
void set_foreach(SET set, void(*func)(RBNODE)) {
    inorder(set->tree->root, func);
}