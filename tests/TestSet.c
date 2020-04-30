/**
 * Test suite for Set unit
 * 
 * @file TestSet.c
 * @author Emma Campbell
 * @date 04-18-2020
 */ 

// Test library
#include <narwhal.h> 

// Unit being tested ---
#include <set.h>

int compare(void *c1, void *c2)
{

    int a = (int)c1;
    int b = (int)c2;

    if (a == b)
    {
        return 0;
    }
    else if (a < b)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void print(RBNODE n)
{
    printf("%c ", (int)n->key);
}

TEST(SET_CREATE){
    SET s = set_create(compare, print);
    ASSERT(s != NULL, "Unable to allocate memory");
}

TEST (SET_INSERT) {
    SET s = set_create(compare, print);
    set_insert(s, (void *)1);
    ASSERT(set_contains(s, (void *)1) == true);
}

TEST (SET_REMOVE) {
    SET s = set_create(compare, print);
    set_insert(s, (void *)2);
    set_remove(s, (void *)2);
    ASSERT(set_contains(s, (void *)2) == false);
}

TEST (SET_UNION) {
    SET s = set_create(compare, print);
    set_insert(s, (void *)14);
    set_insert(s, (void *)22);
    set_insert(s, (void *)3);
    set_insert(s, (void *)1);
    set_insert(s, (void *)5);
    set_insert(s, (void *)89);
    set_insert(s, (void *)12);

    int ssize = s->size;

    SET s2 = set_create(compare, print);
    set_insert(s2, (void *)15);
    set_insert(s2, (void *)23);
    set_insert(s2, (void *)4);
    set_insert(s2, (void *)2);
    set_insert(s2, (void *)6);
    set_insert(s2, (void *)90);
    set_insert(s2, (void *)13);

    int s2size = s2->size;

    SET uni = set_union(s, s2);

    ASSERT(uni->size == ssize + s2size, "Expected %d, got %d", (ssize + s2size), uni->size);
}

TEST (SET_DIFFERENCE) {
    SET s = set_create(compare, print);
    set_insert(s, (void *)4);
    set_insert(s, (void *)5);
    set_insert(s, (void *)6);

    SET s2 = set_create(compare, print);
    set_insert(s2, (void *)3);
    set_insert(s2, (void *)2);
    set_insert(s2, (void *)4);

    SET uni = set_difference(s, s2);

    ASSERT(uni->size == 2, "Expected 2, got %d", uni->size);
}

TEST (SET_INTERSECTION) {
    SET s = set_create(compare, print);
    set_insert(s, (void *)4);
    set_insert(s, (void *)5);
    set_insert(s, (void *)6);

    SET s2 = set_create(compare, print);
    set_insert(s2, (void *)3);
    set_insert(s2, (void *)2);
    set_insert(s2, (void *)4);

    SET uni = set_intersection(s, s2);

    ASSERT(uni->size == 1, "Expected 1, got %d", uni->size);
}

TEST (SET_EQUALS) {
    SET s = set_create(compare, print);
    set_insert(s, (void *)4);
    set_insert(s, (void *)5);
    set_insert(s, (void *)6);

    SET s2 = set_create(compare, print);
    set_insert(s2, (void *)4);
    set_insert(s2, (void *)5);
    set_insert(s2, (void *)6);

    ASSERT(set_equals(s, s2) == true);
}

TEST (SET_DISJOINT) {
    SET s = set_create(compare, print);
    set_insert(s, (void *)4);
    set_insert(s, (void *)5);
    set_insert(s, (void *)6);

    SET s2 = set_create(compare, print);
    set_insert(s2, (void *)7);
    set_insert(s2, (void *)8);
    set_insert(s2, (void *)9);

    ASSERT(set_disjoint(s, s2) == true);
}

TEST (SET_SUBSET) {
    SET s = set_create(compare, print);
    set_insert(s, (void *)4);
    set_insert(s, (void *)5);
    set_insert(s, (void *)6);

    SET s2 = set_create(compare, print);
    set_insert(s2, (void *)6);
    set_insert(s2, (void *)5);

    ASSERT(set_subset(s2, s) == true);
}

TEST (SET_SUPERSET) {
    SET s = set_create(compare, print);
    set_insert(s, (void *)4);
    set_insert(s, (void *)5);
    set_insert(s, (void *)6);

    SET s2 = set_create(compare, print);
    set_insert(s2, (void *)6);
    set_insert(s2, (void *)5);

    ASSERT(set_superset(s, s2) == true);
}

TEST (SET_SUBSET_STRICT) {
    SET s = set_create(compare, print);
    set_insert(s, (void *)4);
    set_insert(s, (void *)5);
    set_insert(s, (void *)6);

    SET s2 = set_create(compare, print);
    set_insert(s2, (void *)4);
    set_insert(s2, (void *)6);
    set_insert(s2, (void *)5);

    ASSERT(set_subset_strict(s, s2) == false);
}

TEST (SET_SUPERSET_STRICT) {
    SET s = set_create(compare, print);
    set_insert(s, (void *)4);
    set_insert(s, (void *)5);
    set_insert(s, (void *)6);

    SET s2 = set_create(compare, print);
    set_insert(s2, (void *)4);
    set_insert(s2, (void *)6);
    set_insert(s2, (void *)5);

    ASSERT(set_superset_strict(s, s2) == false);
}