#ifndef _SET_h
#define _SET_h

#include <common.h>
#include <rbtree.h>

struct set_t {
    RBTREE data;
    int size;
};

typedef set_t *Set;

extern Set set_create(cmp_func_t cmp_func);
extern void set_destroy(Set s);
extern void set_insert(Set s, void *data);
extern void set_remove(Set s, void *data);

extern Set set_join(Set s1, Set s2);
extern Set set_union(Set s1, Set s2);

#endif //_SET_h
