#include <narwhal.h>
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
    ASSERT(rb_create(&cmp_char) != NULL, "Unable to create RBTREE object.");
}


TEST_FIXTURE(tree, RBTREE) {
    
    *tree = rb_create(&cmp_char);

    CLEANUP_FIXTURE(tree) {
        rb_destroy(tree);
    }
}

TEST(RB_INSERT, tree)
{
    rb_insert(tree, (void *)'x');
    ASSERT(rb_find(tree, (void *)'x') != NULL, 'Unable to find inserted object.');  
}