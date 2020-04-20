/**
 * Entry point into application
 * 
 * @file main.c
 * @date 04/18/2020
 */

#include <stdio.h>
#include <rbtree.h>

int cmp_char(void *c1, void *c2) {
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

void do_difference(void)
{
	
    RBTREE t1 = rb_create(&cmp_char);
    rb_insert(t1, (void *)'b');
    rb_insert(t1, (void *)'a');
    rb_insert(t1, (void *)'c');
    rb_insert(t1, (void *)'d');
    rb_insert(t1, (void *)'e');

    print_tree(t1, print_node);
    printf("\n");

    RBTREE t2 = rb_create(&cmp_char);
    rb_insert(t2, (void *)'c');
    rb_insert(t2, (void *)'h');
    rb_insert(t2, (void *)'a');
    rb_insert(t2, (void *)'k');

    print_tree(t2, print_node);
    printf("\n");

    RBTREE diff = rb_difference(t1, t2);
    print_tree(diff, print_node);

    printf("\nSize of difference set: %d.\nExpected: 3", rb_size(diff));
    // rb_destroy(t1);
    // rb_destroy(t2);
}

void do_intersection(void)
{
	
    RBTREE t1 = rb_create(&cmp_char);
    rb_insert(t1, (void *)'b');
    rb_insert(t1, (void *)'a');
    rb_insert(t1, (void *)'c');
    rb_insert(t1, (void *)'d');
    rb_insert(t1, (void *)'e');

    print_tree(t1, print_node);
    printf("\n");

    RBTREE t2 = rb_create(&cmp_char);
    rb_insert(t2, (void *)'c');
    rb_insert(t2, (void *)'h');
    rb_insert(t2, (void *)'a');
    rb_insert(t2, (void *)'k');

    print_tree(t2, print_node);
    printf("\n");

    RBTREE inter = rb_intersection(t1, t2);
    print_tree(inter, print_node);

    printf("\nSize of intersection set: %d\nExpected: 2", rb_size(inter));
    rb_destroy(t1);
    rb_destroy(t2);
}

int main(void)
{
	do_difference();
	// do_intersection();
}
