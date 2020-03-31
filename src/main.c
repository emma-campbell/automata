#include <rbtree.h>
#include <stdio.h>

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

    RBTREE tree = rb_create(&cmp_char);
    rb_insert(tree, (void *)'c');
    rb_insert(tree, (void *)'d');
    rb_insert(tree, (void *)'a');
    rb_insert(tree, (void *)'z');
    rb_insert(tree, (void *)'w');
    rb_insert(tree, (void *)'x');
    print_tree(tree, &print_node);
    rb_destroy(tree);
}