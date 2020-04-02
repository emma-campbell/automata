/**
 * @author Emma Campbell
 * @date 2020-03-24
 *
 * Simple Red-Black Tree implementation. Red-black trees are self-balancing,
 * allowing for traversal in O(log n) time, making them rather efficient for 
 * re(trie)val of items. 
 * 
 * The insertion and deletion, as well as rearranging of the tree also all occur
 * in O(log n) time.
 *
 * **BASIC PROPERTIES OF RED-BLACK TREES**
 *
 * https://en.wikipedia.org/wiki/Red–black_tree
 *
 * 1. Each node is either red or black.
 * 2. The root of the tree is black.
 *  - This rule is sometimes ommited, because the root can be changed from red
 *    to black, but not vice-versa.
 * 3. All leaves are black.
 * 4. If a node is red, then both its children are black.
 * 5. Every path from a given node to any of its descendant NIL (leaf) nodes
 *    goes through the same number of black nodes
 * 
 * A lot of the information and algorithms described come from "Constructing Red
 *  Black Trees", Ralf Hinze 
 * (http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.46.2171&rep=rep1&type=pdf)
 * 
 * TODO: 
 * Implement the set operations on rebblack tree
 */
#ifndef _RBTREE_h
#define _RBTREE_h

#include <common.h>
#include <queue.h>

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
    QUEUE q;
};

typedef struct rb_tree *RBTREE;

extern RBTREE rb_create(cmp_func_t cmp);

/**
 * @brief Find the minimum value of the given tree
 * @param tree Pointer to the tree
 * @returns minimum value of the tree 
 */
extern void *rb_min(RBTREE tree);

/**
 * @brief Find the maximum value of the given tree
 * @param tree Pointer to the tree
 * @returns maximum value of the tree 
 */
extern void *rb_max(RBTREE tree);


//
// Basic Operations
//

/**
 * @brief Insert a item into the RB Tree.
 * @param tree Pointer to the tree
 * @param key Pointer to the item
 * @returns {@code 1} if successful, false otherwise.
 */
extern int rb_insert(RBTREE tree, void *key);

/**
 * @brief Find the node with the given key value.
 * @param tree Pointer to the tree
 * @param key Pointer to the key
 * @returns the node, if found, null otherwise.
 */ 
extern RBNODE rb_find(RBTREE tree, void *key);

/**
 * @brief Remove an item from the tree
 * @param tree Pointer to the tree
 * @param key Item to remove from the tree
 * @returns the key if it exists, otherwise {@code NULL}.
 */
extern RBNODE rb_remove(RBTREE tree, void* key);

/**
 * @brief Clear the allocated storage for the tree
 * @param tree Tree to be destroyed
 */
extern void rb_destroy(RBTREE tree);

/**
 * @brief Prints the elements in the tree by iterating through
 *        the elements and calling the function pointer *func on
 *        each node.
 * 
 * Using a function pointer means that we can call print and 
 * specify the data type that is being printed.
 * 
 * @param tree Pointer to the tree
 * @param func Pointer to the print function.
 */
extern void print_tree(RBTREE tree, void (*func)(RBNODE));

//
// Traversal Operations
//

/**
 * @brief Iterates through the tree in level order
 * @param n Root node
 * @param func Function applied to each node
 */
extern void levelorder(RBTREE tree, void (*func)(RBNODE));

/**
 * @brief Recurses through the tree in preorder
 * @param n Root node
 * @param func Function applied to each node
 */
extern void preorder(RBNODE n, void (*func)(RBNODE));

/**
 * @brief Recurses through the tree in postorder
 * @param n Root node
 * @param func Function applied to each node
 */
extern void postorder(RBNODE n, void (*func)(RBNODE));

/**
 * @brief Recurses through the tree in inorder
 * @param n Root node
 * @param func Function applied to each node
 */
extern void inorder(RBNODE n, void (*func)(RBNODE));

//
// Set Operations
//
// TODO: Implement RB Set Operations

// extern RBTREE rb_join(RBTREE t1, RBTREE t2);
// extern RBTREE rb_union(RBTREE t1, RBTREE t2);
// extern RBTREE rb_intersection(RBTREE t1, RBTREE t2);

#endif // _RBTREE_h