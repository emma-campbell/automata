#include <narwhal.h>
#include <stdbool.h>

#include <rbtree.h>
#include <char_functions.h>

TEST(RB_CONSTRUCTOR) {
    ASSERT(rb_create(CMP_CHAR) != NULL);
}

TEST(RB_INSERT)
{
    RBTREE tree = rb_create(CMP_CHAR);
    rb_insert(tree, CHAR2VOIDP('x'));
    ASSERT(rb_find(tree, CHAR2VOIDP('x')) != NULL); 
}

TEST (RB_NO_DUPLICATE_KEYS) {
    RBTREE tree = rb_create(CMP_CHAR);
    rb_insert(tree, CHAR2VOIDP('x'));
    rb_insert(tree, CHAR2VOIDP('x'));

    ASSERT(rb_size(tree) == 1);
}

TEST(RB_REMOVE) 
{
    RBTREE tree = rb_create(CMP_CHAR);
    rb_insert(tree, CHAR2VOIDP('x'));
    rb_insert(tree, CHAR2VOIDP('a'));
    rb_insert(tree, CHAR2VOIDP('c'));
    rb_insert(tree, CHAR2VOIDP('y'));
    rb_insert(tree, CHAR2VOIDP('h'));
    
    rb_remove(tree, CHAR2VOIDP('a'));

    ASSERT(rb_find(tree, CHAR2VOIDP('a')) == NULL);
}

TEST (RB_MAX) {
    RBTREE tree = rb_create(CMP_CHAR);
    rb_insert(tree, CHAR2VOIDP('x'));
    rb_insert(tree, CHAR2VOIDP('a'));
    rb_insert(tree, CHAR2VOIDP('c'));
    rb_insert(tree, CHAR2VOIDP('y'));
    rb_insert(tree, CHAR2VOIDP('h'));
    ASSERT(rb_max(tree) == CHAR2VOIDP('y'));
}

TEST (RB_MIN) {
    RBTREE tree = rb_create(CMP_CHAR);
    rb_insert(tree, CHAR2VOIDP('x'));
    rb_insert(tree, CHAR2VOIDP('a'));
    rb_insert(tree, CHAR2VOIDP('c'));
    rb_insert(tree, CHAR2VOIDP('y'));
    rb_insert(tree, CHAR2VOIDP('h'));
    ASSERT(rb_min(tree) == CHAR2VOIDP('a'));
}

TEST (RB_HEIGHT) {
    RBTREE tree = rb_create(CMP_CHAR);
    rb_insert(tree, CHAR2VOIDP('x'));
    rb_insert(tree, CHAR2VOIDP('a'));
    rb_insert(tree, CHAR2VOIDP('c'));
    rb_insert(tree, CHAR2VOIDP('y'));
    rb_insert(tree, CHAR2VOIDP('h'));
    ASSERT(rb_height(tree) == 3, "Expected 3, got %d", rb_height(tree));
}


/**
 * According to "An Overview of Red-Black and Finger Trees" by Heather D. Booth (U. Tennessee)
 * A Red-Black tree with root w/ rank r has a height greater than r, but less than 2r.
 * 
 * We use this to test the validity of the rank function.
 */
TEST (RB_RANK) {
    RBTREE tree = rb_create(CMP_CHAR);
    rb_insert(tree, CHAR2VOIDP('x'));
    rb_insert(tree, CHAR2VOIDP('a'));
    rb_insert(tree, CHAR2VOIDP('c'));
    rb_insert(tree, CHAR2VOIDP('y'));
    rb_insert(tree, CHAR2VOIDP('h'));

    int h = rb_height(tree);
    int r = rb_rank(tree);

    ASSERT(r <= h && h <= 2*r);
}

TEST (RB_SIZE) {
    RBTREE tree = rb_create(CMP_CHAR);
    rb_insert(tree, CHAR2VOIDP('x'));
    rb_insert(tree, CHAR2VOIDP('a'));
    rb_insert(tree, CHAR2VOIDP('c'));
    rb_insert(tree, CHAR2VOIDP('y'));
    rb_insert(tree, CHAR2VOIDP('h'));

    ASSERT(rb_size(tree) == 5);
}

TEST (RB_JOIN) {

    RBTREE t1 = rb_create(CMP_CHAR);
    rb_insert(t1, CHAR2VOIDP('b'));
    rb_insert(t1, CHAR2VOIDP('a'));
    rb_insert(t1, CHAR2VOIDP('c'));
    rb_insert(t1, CHAR2VOIDP('d'));
    rb_insert(t1, CHAR2VOIDP('e'));
    
    int t1_size = rb_size(t1);

    RBTREE t2 = rb_create(CMP_CHAR);
    rb_insert(t2, CHAR2VOIDP('f'));
    rb_insert(t2, CHAR2VOIDP('g'));
    rb_insert(t2, CHAR2VOIDP('h'));
    rb_insert(t2, CHAR2VOIDP('i'));
    rb_insert(t2, CHAR2VOIDP('j'));
    rb_insert(t2, CHAR2VOIDP('k'));

    int t2_size = rb_size(t2);

    RBTREE join = rb_join(t1, t2);
    int join_size = rb_size(join);
    
    ASSERT(rb_size(join) == (t1_size + t2_size), "Size should be %d but got %d.", (t1_size + t2_size), join_size);
}

TEST (RB_JOIN_NO_DUPLICATES) {
    RBTREE t1 = rb_create(CMP_CHAR);
    rb_insert(t1, CHAR2VOIDP('b'));
    rb_insert(t1, CHAR2VOIDP('a'));
    rb_insert(t1, CHAR2VOIDP('c'));
    rb_insert(t1, CHAR2VOIDP('d'));
    rb_insert(t1, CHAR2VOIDP('e'));

    int t1_size = rb_size(t1);

    RBTREE t2 = rb_create(CMP_CHAR);
    rb_insert(t2, CHAR2VOIDP('f'));
    rb_insert(t2, CHAR2VOIDP('g'));
    rb_insert(t2, CHAR2VOIDP('h'));
    rb_insert(t2, CHAR2VOIDP('d'));
    rb_insert(t2, CHAR2VOIDP('j'));
    rb_insert(t2, CHAR2VOIDP('k'));

    int t2_size = rb_size(t2);

    RBTREE join = rb_join(t1, t2);
    int join_size = rb_size(join);

    ASSERT(
        rb_size(join) == (t1_size + t2_size), 
        "Size should be %d but got %d.", 
        ((t1_size + t2_size) - 1), 
        join_size
    );
}

TEST (RB_DIFFERENCE) {
    RBTREE t1 = rb_create(CMP_CHAR);
    rb_insert(t1, CHAR2VOIDP('b'));
    rb_insert(t1, CHAR2VOIDP('a'));
    rb_insert(t1, CHAR2VOIDP('c'));
    rb_insert(t1, CHAR2VOIDP('d'));
    rb_insert(t1, CHAR2VOIDP('e'));
    rb_insert(t1, CHAR2VOIDP('g'));
    

    print_tree(t1, PRINT_CHAR);
    printf("\n");

    RBTREE t2 = rb_create(CMP_CHAR);
    rb_insert(t2, CHAR2VOIDP('c'));
    rb_insert(t2, CHAR2VOIDP('h'));
    rb_insert(t2, CHAR2VOIDP('a'));
    rb_insert(t2, CHAR2VOIDP('k'));

    print_tree(t2, PRINT_CHAR);
    printf("\n");

    RBTREE diff = rb_difference(t1, t2);
    print_tree(diff, PRINT_CHAR);

    ASSERT(
        rb_size(diff) == 4,
        "Size should be 4 but got %d.",
        rb_size(diff));
}

TEST (RB_INTERSECTION) {
    RBTREE t1 = rb_create(CMP_CHAR);
    rb_insert(t1, CHAR2VOIDP('b'));
    rb_insert(t1, CHAR2VOIDP('a'));
    rb_insert(t1, CHAR2VOIDP('c'));
    rb_insert(t1, CHAR2VOIDP('d'));
    
    print_tree(t1, PRINT_CHAR);
    printf("\n");

    RBTREE t2 = rb_create(CMP_CHAR);
    rb_insert(t2, CHAR2VOIDP('c'));
    rb_insert(t2, CHAR2VOIDP('h'));
    rb_insert(t2, CHAR2VOIDP('a'));
    rb_insert(t2, CHAR2VOIDP('k'));

    print_tree(t2, PRINT_CHAR);
    printf("\n");

    RBTREE inter = rb_intersection(t1, t2);
    print_tree(inter, PRINT_CHAR);

    ASSERT(
        rb_size(inter) == 2,
        "Size should be 2 but got %d.",
        rb_size(inter));
}

TEST (RB_TO_ARRAY) {

    RBTREE t1 = rb_create(CMP_CHAR);
    rb_insert(t1, CHAR2VOIDP('b'));
    rb_insert(t1, CHAR2VOIDP('a'));
    rb_insert(t1, CHAR2VOIDP('c'));
    rb_insert(t1, CHAR2VOIDP('d'));

    print_tree(t1, PRINT_CHAR);
    printf("\n");

    void **arr = rb_to_array(t1);

    int size = 0;

    while (arr[size] != NULL) {
        printf("%c ", (char)arr[size++]);
    }

    ASSERT(size == 4, "Expected array of size 4, got %d", size);
}

TEST (RB_EQUALS) {
    RBTREE t1 = rb_create(CMP_CHAR);
    rb_insert(t1, CHAR2VOIDP('b'));
    rb_insert(t1, CHAR2VOIDP('a'));
    rb_insert(t1, CHAR2VOIDP('c'));
    rb_insert(t1, CHAR2VOIDP('d'));

    RBTREE t2 = rb_create(CMP_CHAR);
    rb_insert(t2, CHAR2VOIDP('b'));
    rb_insert(t2, CHAR2VOIDP('a'));
    rb_insert(t2, CHAR2VOIDP('c'));
    rb_insert(t2, CHAR2VOIDP('d'));

    ASSERT(rb_equals(t1, t2) == true, "Expected true, got false.");
}

TEST (RB_IS_DISJOINT) {
    RBTREE t1 = rb_create(CMP_CHAR);
    rb_insert(t1, CHAR2VOIDP('b'));
    rb_insert(t1, CHAR2VOIDP('a'));
    rb_insert(t1, CHAR2VOIDP('c'));
    rb_insert(t1, CHAR2VOIDP('d'));

    RBTREE t2 = rb_create(CMP_CHAR);
    rb_insert(t2, CHAR2VOIDP('b'));
    rb_insert(t2, CHAR2VOIDP('a'));
    rb_insert(t2, CHAR2VOIDP('c'));
    rb_insert(t2, CHAR2VOIDP('d'));

    RBTREE t3 = rb_create(CMP_CHAR);
    rb_insert(t3, CHAR2VOIDP('z'));
    rb_insert(t3, CHAR2VOIDP('y'));
    rb_insert(t3, CHAR2VOIDP('x'));
    rb_insert(t3, CHAR2VOIDP('w'));

    ASSERT(rb_is_disjoint(t1, t3) == true, "Excepted true, got false (t1, t3)");
    ASSERT(rb_is_disjoint(t1, t2) == false, "Expected false, got true (t1, t2)");
}

TEST (RB_IS_SUBSET) {
    RBTREE t1 = rb_create(CMP_CHAR);
    rb_insert(t1, CHAR2VOIDP('b'));
    rb_insert(t1, CHAR2VOIDP('a'));
    rb_insert(t1, CHAR2VOIDP('c'));
    rb_insert(t1, CHAR2VOIDP('d'));

    RBTREE t2 = rb_create(CMP_CHAR);
    rb_insert(t2, CHAR2VOIDP('b'));
    rb_insert(t2, CHAR2VOIDP('a'));

    ASSERT(rb_is_subset(t2, t1) == true, "Expected true, got false (t2, t1)");
    ASSERT(rb_is_subset(t1, t2) == false, "Expected false, got true (t2, t1)");
}

TEST(RB_IS_SUPERSET)
{
    RBTREE t1 = rb_create(CMP_CHAR);
    rb_insert(t1, CHAR2VOIDP('b'));
    rb_insert(t1, CHAR2VOIDP('a'));
    rb_insert(t1, CHAR2VOIDP('c'));
    rb_insert(t1, CHAR2VOIDP('d'));

    RBTREE t2 = rb_create(CMP_CHAR);
    rb_insert(t2, CHAR2VOIDP('b'));
    rb_insert(t2, CHAR2VOIDP('a'));

    ASSERT(rb_is_superset(t1, t2) == true, "Expected true, got false (t2, t1)");
    ASSERT(rb_is_superset(t2, t1) == false, "Expected false, got true (t2, t1)");
}

TEST(RB_IS_SUBSET_STRICT)
{
    RBTREE t1 = rb_create(CMP_CHAR);
    rb_insert(t1, CHAR2VOIDP('b'));
    rb_insert(t1, CHAR2VOIDP('a'));
    rb_insert(t1, CHAR2VOIDP('c'));
    rb_insert(t1, CHAR2VOIDP('d'));

    RBTREE t2 = rb_create(CMP_CHAR);
    rb_insert(t2, CHAR2VOIDP('b'));
    rb_insert(t2, CHAR2VOIDP('a'));

    RBTREE t3 = rb_create(CMP_CHAR);
    rb_insert(t3, CHAR2VOIDP('b'));
    rb_insert(t3, CHAR2VOIDP('a'));

    ASSERT(rb_is_subset_strict(t2, t1) == true, "Expected true, got false (t2, t1)");
    ASSERT(rb_is_subset_strict(t2, t3) == false, "Expected false, got true (t2, t3)");
}

TEST(RB_IS_SUEPRSET_STRICT)
{
    RBTREE t1 = rb_create(CMP_CHAR);
    rb_insert(t1, CHAR2VOIDP('b'));
    rb_insert(t1, CHAR2VOIDP('a'));
    rb_insert(t1, CHAR2VOIDP('c'));
    rb_insert(t1, CHAR2VOIDP('d'));

    RBTREE t2 = rb_create(CMP_CHAR);
    rb_insert(t2, CHAR2VOIDP('b'));
    rb_insert(t2, CHAR2VOIDP('a'));

    RBTREE t3 = rb_create(CMP_CHAR);
    rb_insert(t3, CHAR2VOIDP('b'));
    rb_insert(t3, CHAR2VOIDP('a'));
    rb_insert(t3, CHAR2VOIDP('c'));
    rb_insert(t3, CHAR2VOIDP('d'));

    ASSERT(rb_is_superset_strict(t1, t2) == true, "Expected true, got false (t2, t1)");
    ASSERT(rb_is_superset_strict(t1, t3) == false, "Expected false, got true (t2, t3)");
}