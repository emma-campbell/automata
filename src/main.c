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

    RBTREE t1 = rb_create(&cmp_char);
    rb_insert(t1, (void *)'b');
    rb_insert(t1, (void *)'a');
    rb_insert(t1, (void *)'c');
    rb_insert(t1, (void *)'d');
    rb_insert(t1, (void *)'e');

    RBTREE t2 = rb_create(&cmp_char);
    rb_insert(t2, (void *)'f');
    rb_insert(t2, (void *)'g');
    rb_insert(t2, (void *)'h');
    rb_insert(t2, (void *)'i');
    rb_insert(t2, (void *)'j');
    rb_insert(t2, (void *)'k');

    RBTREE join2 = rb_join(t1, t2);
    print_tree(join2, print_node);

    RBTREE split = rb_split(join2, (void *)'i');
    print_tree(split, print_node);
}