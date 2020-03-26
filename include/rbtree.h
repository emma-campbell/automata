/**
 * @author Emma Campbell
 * @date 2020-03-24
 *
 * Simple Red-Black Tree implementation. Red-black trees are self-balancing, allowing for
 * traversal in O(log n) time, making them rather efficient for re(trie)val of items. 
 * The insertion and deletion, as well as rearranging of the tree also all occur in 
 * O(log n) time.
 *
 *
 * **BASIC PROPERTIES OF RED-BLACK TREES**
 *
 * https://en.wikipedia.org/wiki/Red–black_tree
 *
 * 1. Each node is either red or black.
 * 2. The root of the tree is black.
 *  - This rule is sometimes ommited, because the root can be changed from red to black,
 *    but not vice-versa.
 * 3. All leaves are black.
 * 4. If a node is red, then both its children are black.
 * 5. Every path from a given node to any of its descendant NIL (leaf) nodes goes 
 *    through the same number of black nodes
 * 
 * TODO: 
 * Add comments describing the ways the functions work, rb_destroy & rb_clear. Once done, add test cases. 
 */
#ifndef _RBTREE_h
#define _RBTREE_h

#include <common.h>

enum color_t { BLACK, RED };
typedef enum color_t COLOR;

struct rb_node {
    struct rb_node *right;  //pointer to the right child
    struct rb_node *left;   //pointer to the left child
    struct rb_node *parent; //pointer to the parent node

    COLOR color;
    void *key;
};

typedef struct rb_node *RBNODE;
typedef int (*cmp_func_t)(void*, void*);

struct rb_tree {
    RBNODE root;
    cmp_func_t cmp;
};

typedef struct rb_tree *RBTREE;

extern RBTREE rb_create(cmp_func_t cmp);
extern int rb_insert(RBTREE tree, void *key);
extern void* rb_remove(RBTREE tree, const void* key);

extern void print_tree(RBTREE tree, void (*func)(RBNODE));
extern void levelorder(RBNODE n, void (*func)(RBNODE));
extern void preorder(RBNODE n, void (*func)(RBNODE));
extern void postorder(RBNODE n, void (*func)(RBNODE));
extern void inorder(RBNODE n, void (*func)(RBNODE));

#endif // _RBTREE_h
