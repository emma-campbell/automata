/**
 * @author Emma Campbell
 * @date 2020-03-24
 * 
 * TODO: 
 * Implement the set operations on rebblack tree
 */

#ifndef _RBTREE_h
#define _RBTREE_h

#include <common.h>
#include <queue.h>

/**
 * Simple Red-Black Tree Implementation. Red-Black trees are 
 * self-balancing, allowing for traversal in O(log n) time, making
 * them rather efficient for the re(trie)val of items.
 * 
 * The insertion and deletion, as well as rebalancing of the tree also 
 * all occur in O(log n) time.
 * 
 * BASIC PROPERTIES
 * 1. Each node is either red or black
 * 2. The root of the tree is black
 *      - This rule is sometimes ommitted since the root can be changed
 *        from red to black, but not vice-versa.
 * 3. All leaves are black.
 * 4. If a node is red, then both its children are black.
 * 5. Every path from a given node to any of its descendant leaf nodes
 *    goes through the same number of black nodes (referred to as RANK)
 * 
 * SOURCES
 * [https://en.wikipedia.org/wiki/Red–black_tree]
 * [http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.46.2171&rep=rep1&type=pdf]
 */

enum color_t
{
    BLACK,
    RED
};
typedef enum color_t COLOR;

struct rb_node
{
    struct rb_node *right;  //pointer to the right child
    struct rb_node *left;   //pointer to the left child
    struct rb_node *parent; //pointer to the parent node

    COLOR color;
    void *key;
};

typedef struct rb_node *RBNODE;
typedef int (*cmp_func_t)(void *, void *);

struct rb_tree
{
    RBNODE root;
    cmp_func_t cmp;
    QUEUE q;
};

typedef struct rb_tree *RBTREE;

/**
 * @brief Allocate space for a new Red-Black tree.
 * @param cmp Comparison function used to traverse the tree.
 * @returns new RBTREE.
 */
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

/**
 * @brief Find the maximum height of the given tree (should be maximum O(log(n)))
 * @param tree Pointer to the tree
 * @returns the height of the tree
 */
extern int rb_height(RBTREE tree);

/**
 * @brief Find the rank of the tree from its root
 * @param tree Pointer to the tree
 * @returns the number of black nodes between the root of the tree and any given leaf.
 */
extern int rb_rank(RBTREE tree);

/**
 * @brief Returns the number of nodes in the tree
 * @param tree Pointer to the tree
 * @returns the number of nodes in the tree.
 */
extern int rb_size(RBTREE tree);

// ///////////////////////////////////////////////////////////
// Basic Operations
// ///////////////////////////////////////////////////////////

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
extern RBNODE rb_remove(RBTREE tree, void *key);

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

// //////////////////////////////////////////////////////////////////
// Traversal Operations
// //////////////////////////////////////////////////////////////////

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

// ////////////////////////////////////////////////////////////////////
// Set Operations
// ////////////////////////////////////////////////////////////////////

// TODO: Implement RB Set Operations

/**
 * @brief Joins two Red-Black trees, t1 and t2 and returns a    
 *        red-black tree T such that 
 *                   T = t1 U {x} U t2 
 * @param t1 the first red-black tree in the join
 * @param t2 the second red-black tree in the join
 * @returns a new red-black tree that is the result of the join
 *          of t1 U t2
 * 
 * NOTE: An important assumption here is that the elements of t1 will all be
 * smaller than any element that exists in t2. 
 */
extern RBTREE rb_join(RBTREE t1, RBTREE t2);

/**
 * @brief Return the union of two red black trees
 * @param s1 Pointer to the first rbtree
 * @param s2 Pointer to the second rbtree
 * @return A new rbtree with the elements in s1 or s2
 * 
 * The union of two sets A and B, denoted A u B = { x : x ∈ A v x ∈ B }
 */
extern RBTREE rb_union(RBTREE A, RBTREE B);

/**
 * @brief Return the difference A - B
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @param A new rbtree with the elements in A and not B
 * 
 * The difference of two sets A and B, denoted A - B = { x : x ∈ A ^ x ∉ B }
 */
extern RBTREE rb_difference(RBTREE A, RBTREE B);

/**
 * @brief Returns the intersection A n B
 * @param A Pointer to the first set
 * @param B Pointer to the second set
 * @returns new rbtree with elements 
 * 
 * The intersection of two sets A and B, denoted A n B = { x : x ∈ A ^ x ∈ B }
 */
extern RBTREE rb_intersection(RBTREE A, RBTREE B);

#endif // _RBTREE_h