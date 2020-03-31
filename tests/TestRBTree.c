#include "narwhal.h"
#include <rbtree.h>

int cmp_char(void *c1, void *c2)
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

void print_node(RBNODE n)
{
    printf("%c ", (char)n->key);
}

TEST(RB_CONSTRUCTOR) {
    ASSERT(rb_create(&cmp_char) != NULL);
}

TEST(RB_INSERT)
{
    RBTREE tree = rb_create(&cmp_char);
    rb_insert(tree, (void *)'x');
    ASSERT(rb_find(tree, (void *)'x') != NULL); 
}

TEST(RB_REMOVE) 
{
    RBTREE tree = rb_create(&cmp_char);
    rb_insert(tree, (void *)'x');
    rb_insert(tree, (void *)'a');
    rb_insert(tree, (void *)'c');
    rb_insert(tree, (void *)'y');
    rb_insert(tree, (void *)'h');
    
    rb_remove(tree, (void *)'a');

    ASSERT(rb_find(tree, (void *)'a') == NULL);
}