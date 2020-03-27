#include <rbtree.h>
#include <stdio.h>
#include <string.h>

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

int main(void)
{
    RBTREE t = rb_create(&cmp_char);
    
    rb_insert(t, (void *)'c');
    rb_insert(t, (void *)'y');
    rb_insert(t, (void *)'a');
    rb_insert(t, (void *)'z');
    rb_insert(t, (void *)'e');

    // RBNODE node = rb_find(t, (void*)'c');

    rb_insert(t, (void *)'x');
    rb_insert(t, (void *)'r');
    rb_insert(t, (void *)'q');
    rb_insert(t, (void *)'d');
    print_tree(t, &print_node);
    rb_destroy(t);
}
