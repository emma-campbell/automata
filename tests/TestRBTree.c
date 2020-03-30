#include <unity.h>
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

// run before and after each test!
void setup(void) {}
void tearDown(void) {}


void test_rb_create()
{
    RBTREE tree = rb_create(&cmp_char);
    TEST_ASSERT_NOT_NULL(tree);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_rb_create);
    RETURN UNITY_END();
}
