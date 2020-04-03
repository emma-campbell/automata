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

TEST (RB_MAX) {
    RBTREE tree = rb_create(&cmp_char);
    rb_insert(tree, (void *)'x');
    rb_insert(tree, (void *)'a');
    rb_insert(tree, (void *)'c');
    rb_insert(tree, (void *)'y');
    rb_insert(tree, (void *)'h');
    ASSERT(rb_max(tree) == (void *)'y');
}

TEST (RB_MIN) {
    RBTREE tree = rb_create(&cmp_char);
    rb_insert(tree, (void *)'x');
    rb_insert(tree, (void *)'a');
    rb_insert(tree, (void *)'c');
    rb_insert(tree, (void *)'y');
    rb_insert(tree, (void *)'h');
    ASSERT(rb_min(tree) == (void *)'a');
}

TEST (RB_HEIGHT) {
    RBTREE tree = rb_create(&cmp_char);
    rb_insert(tree, (void *)'x');
    rb_insert(tree, (void *)'a');
    rb_insert(tree, (void *)'c');
    rb_insert(tree, (void *)'y');
    rb_insert(tree, (void *)'h');
    ASSERT(rb_height(tree) == 3);
}


/**
 * According to "An Overview of Red-Black and Finger Trees" by Heather D. Booth (U. Tennessee)
 * A Red-Black tree with root w/ rank r has a height greater than r, but less than 2r.
 * 
 * We use this to test the validity of the rank function.
 */
TEST (RB_RANK) {
    RBTREE tree = rb_create(&cmp_char);
    rb_insert(tree, (void *)'x');
    rb_insert(tree, (void *)'a');
    rb_insert(tree, (void *)'c');
    rb_insert(tree, (void *)'y');
    rb_insert(tree, (void *)'h');

    int h = rb_height(tree);
    int r = rb_rank(tree);

    ASSERT(r <= h && h <= 2*r);
}

TEST (RB_SIZE) {
    RBTREE tree = rb_create(&cmp_char);
    rb_insert(tree, (void *)'x');
    rb_insert(tree, (void *)'a');
    rb_insert(tree, (void *)'c');
    rb_insert(tree, (void *)'y');
    rb_insert(tree, (void *)'h');

    ASSERT(rb_size(tree) == 5);
}

TEST (RB_JOIN) {

    RBTREE t1 = rb_create(&cmp_char);
    rb_insert(t1, (void *)'b');
    rb_insert(t1, (void *)'a');
    rb_insert(t1, (void *)'c');
    rb_insert(t1, (void *)'d');
    rb_insert(t1, (void *)'e');
    
    int t1_size = rb_size(t1);

    RBTREE t2 = rb_create(&cmp_char);
    rb_insert(t2, (void *)'f');
    rb_insert(t2, (void *)'g');
    rb_insert(t2, (void *)'h');
    rb_insert(t2, (void *)'i');
    rb_insert(t2, (void *)'j');
    rb_insert(t2, (void *)'k');

    int t2_size = rb_size(t2);

    RBTREE join = rb_join(t1, t2);
    int join_size = rb_size(join);
    
    ASSERT(rb_size(join) == (t1_size + t2_size), "Size should be %d but got %d.", (t1_size + t2_size), join_size);
}