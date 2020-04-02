/**
 * 
 */
#include <rbtree.h>

#include <stdlib.h>
#include <stdio.h>

// Node specific functions
RBNODE node_create(void *key);
RBNODE parent(RBNODE n);
RBNODE grandparent(RBNODE n);
RBNODE sibling(RBNODE n);
RBNODE uncle(RBNODE n);
void free_node(RBNODE n);

// rotation functions
void rotate_left(RBNODE n);
void rotate_right(RBNODE n);

// min . max
RBNODE find_subtree_max(RBNODE n);
RBNODE find_subtree_min(RBNODE n);

//
// tree utils
RBNODE find_node(RBNODE root, void *key, cmp_func_t cmp);
void swap(RBNODE n, RBNODE m);
int find_subtree_height(RBNODE n);
int find_node_rank(RBNODE n);
int find_subtree_size(RBNODE n);

//
// Declaring the insertion helpers
void insert_case_1(RBNODE n);
void insert_case_2(RBNODE n);
void insert_case_3(RBNODE n);
void insert_case_4(RBNODE n);
void __repair_insert(RBNODE n);
void insert_recursive(RBNODE root, RBNODE n, cmp_func_t cmp);
RBNODE insert(RBNODE root, RBNODE n, cmp_func_t cmp);

//
// Declaring deletion helpers

void delete_one_child(RBTREE tree, RBNODE n);

void delete_case_1(RBTREE tree, RBNODE n);
void delete_case_2(RBTREE tree, RBNODE n);
void delete_case_3(RBTREE tree, RBNODE n);
void delete_case_4(RBTREE tree, RBNODE n);
void delete_case_5(RBTREE tree, RBNODE n);
void delete_case_6(RBTREE tree, RBNODE n);

//
// Traversal helpers
void levelorder__help(RBNODE root, QUEUE q, void (*func)(RBNODE));

////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////

RBTREE rb_create(cmp_func_t cmp)
{
    RBTREE tree = malloc(sizeof(struct rb_tree));
    assert(tree);

    tree->cmp = cmp;
    tree->q = create_queue();
    return tree;
}

void rb_destroy(RBTREE tree)
{
    RBNODE tmp = tree->root;
    postorder(tmp, free_node);
    free(tree);
}

void *rb_max(RBTREE tree)
{
    RBNODE n = find_subtree_max(tree->root);
    return n->key;
}

void *rb_min(RBTREE tree)
{
    RBNODE n = find_subtree_min(tree->root);
    return n->key;
}

int rb_insert(RBTREE tree, void *key)
{
    RBNODE new_node = node_create(key);
    tree->root = insert(tree->root, new_node, tree->cmp);
    return 1;
};

RBNODE rb_find(RBTREE tree, void *key)
{
    return find_node(tree->root, key, tree->cmp);
}

RBNODE rb_remove(RBTREE t, void *key)
{
    RBNODE node;
    RBNODE min;

    if (t->root == NULL)
        return NULL;

    node = rb_find(t, key);

    if (node == NULL)
        return NULL;

    if (node->left && node->right)
    {
        min = find_subtree_min(node->right);
        swap(node, min);
        node = min;
    }

    delete_one_child(t, node);
    return node;
}

int rb_height(RBTREE tree)
{
    return find_subtree_height(tree->root);
}

int rb_rank(RBTREE tree)
{
    return find_node_rank(tree->root);
}

int rb_size(RBTREE tree)
{
    return find_subtree_size(tree->root);
}

RBTREE rb_join(RBTREE t1, RBTREE t2)
{

    int t1r = rb_rank(t1);
    int t2r = rb_rank(t2);

    RBTREE joined_tree = rb_create(t1->cmp);

    if (t1r > t2r) /* Assume T1 has larger rank */
    {
        // According to a Stanford lecture on balancing trees,
        // if you don't have some key K to join the two trees
        // with, delete the minimum value from the tree with
        // the smaller rank, and use that value to join the
        // two trees.
        //
        // http://web.stanford.edu/class/archive/cs/cs166/cs166.1146/lectures/03/Small03.pdf

        RBNODE root = rb_remove(t2, rb_min(t2));
        RBNODE v = t1->root;

        while (v != NULL)
        { /* Walk down the right of t1 */

            if (find_node_rank(v) == t2r)
            {
                // We found the node w/ the same rank as t2
                break;
            }

            v = v->right;
        }

        RBNODE p = parent(v);

        // Using our joining node (root), let v be its left
        // child, and the root of t2 be its right.
        root->left = v;
        root->right = t2->root;

        if (p != NULL)
        {
            p->right = root;
        }

        __repair_insert(root);

        rb_destroy(t2);
        rb_destroy(t1);

        joined_tree->root = root;
    }
    else /* if t2 has the larger rank, do the same but mirrored*/
    {
        RBNODE root = rb_remove(t1, rb_min(t1));
        RBNODE v = t2->root;

        while (v != NULL)
        {

            if (find_node_rank(v) == t1r)
            {
                break;
            }

            v = v->right;
        }

        RBNODE p = parent(v);

        root->left = v;
        root->right = t1->root;

        if (p != NULL)
        {
            p->right = root;
        }

        __repair_insert(root);

        rb_destroy(t2);
        rb_destroy(t1);

        joined_tree->root = root;
    }

    return joined_tree;
}

void levelorder(RBTREE tree, void (*func)(RBNODE))
{
    levelorder__help(tree->root, tree->q, func);
}

void levelorder__help(RBNODE root, QUEUE q, void (*func)(RBNODE))
{
    if (root == NULL)
        return;

    enqueue(q, (void *)root);

    while (!is_empty(q))
    {
        RBNODE curr = (RBNODE)pop_front(q);
        func(curr);

        if (curr->left != NULL)
            enqueue(q, (void *)curr->left);

        if (curr->right != NULL)
            enqueue(q, (void *)curr->right);

        dequeue(q);
    }
}

void preorder(RBNODE n, void (*func)(RBNODE))
{
    if (n == NULL)
    {
        return;
    }

    func(n);

    if (n->left != NULL)
    {
        preorder(n->left, func);
    }

    if (n->right != NULL)
    {
        preorder(n->right, func);
    }
}

void postorder(RBNODE n, void (*func)(RBNODE))
{
    if (n == NULL)
        return;

    if (n->left != NULL)
    {
        postorder(n->left, func);
    }

    if (n->right != NULL)
    {
        postorder(n->right, func);
    }

    func(n);
}

void inorder(RBNODE n, void (*func)(RBNODE))
{
    if (n == NULL)
        return;

    if (n->left != NULL)
    {
        inorder(n->left, func);
    }

    func(n);

    if (n->right != NULL)
    {
        inorder(n->right, func);
    }
}

void print_tree(RBTREE tree, void (*func)(RBNODE))
{
    inorder(tree->root, func);
}

//////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
//////////////////////////////////////////////////////////////////

// Node Helpers ------------------------------

/**
 * @brief creates the storage space for a new node
 * @param key data to be stored in the node
 * @returns new RBNODE
 */
RBNODE node_create(void *key)
{
    RBNODE n = malloc(sizeof(struct rb_node));
    assert(n != NULL);

    n->key = key;
    n->color = RED;
    return n;
};

/**
 * @brief returns the parent node of the given
 * @param n pointer to the node that we're getting the parent of
 * @returns pointer to the parent node
 */
RBNODE parent(RBNODE n)
{
    return n == NULL ? NULL : n->parent;
};

/**
 * @brief returns the grandparent of the given node
 * @param n pointer to the node we're getting the grandparent of
 * @returns pointer to the grandparent node
 */
RBNODE grandparent(RBNODE n)
{
    return parent(parent(n));
};

/**
 * @brief returns the sibling of the given node
 * @param n pointer to the node we're getting the sibling of
 * @returns pointer to the sibling node
 */
RBNODE sibling(RBNODE n)
{
    RBNODE p = parent(n);

    if (p == NULL)
        return NULL;

    if (n == p->left)
        return p->right;
    else
        return p->left;
}

/**
 * @brief returns the uncle of the given node
 * @param n pointer to the node we're getting the uncle on
 * @returns pointer to the uncle node
 */
RBNODE uncle(RBNODE n)
{
    RBNODE p = parent(n);
    return sibling(p);
}

/**
 * @brief returns the color of the node, black if the pointer is NULL.
 * @param n pointer to the node we're getting the color of
 * @returns COLOR.BLACK if {@code n->color == BLACK || n == NULL }
 */
COLOR node_color(RBNODE n)
{

    if (!n)
        return BLACK;
    else
        return n->color;
}

/**
 * @brief rotates the the given node to the left
 * @param n pointer to the node
 */
void rotate_left(RBNODE n)
{
    RBNODE tmp = n->right;
    RBNODE p = parent(n);

    assert(tmp != NULL);

    n->right = tmp->left;
    tmp->left = n;
    n->parent = tmp;

    if (n->right != NULL)
        n->right->parent = n;

    if (p != NULL)
    {
        if (n == p->left)
        {
            p->left = tmp;
        }
        else if (n == p->right)
        {
            p->right = tmp;
        }
    }
    tmp->parent = p;
}

/**
 * @brief rotates the given node to the left
 * @param n pointer to node
 */
void rotate_right(RBNODE n)
{
    RBNODE tmp = n->left;
    RBNODE p = parent(n);

    assert(tmp != NULL);

    n->left = tmp->right;
    tmp->right = n;
    n->parent = tmp;

    if (n->left != NULL)
        n->left->parent = n;

    if (p != NULL)
    {
        if (n == p->left)
        {
            p->left = tmp;
        }
        else if (n == p->right)
        {
            p->right = tmp;
        }
    }

    tmp->parent = p;
}

/**
 * @brief frees the memory allocated for the node
 * @param n node to be freed
 */
void free_node(RBNODE n)
{
    free(n);
}

/**
 * @brief finds the minumum tree from the given root
 * @param n the root of the tree to find min. of.
 */
RBNODE find_subtree_min(RBNODE n)
{

    while (n->left)
        n = n->left;
    return n;
}

/**
 * @brief finds the maximum tree from the given root
 * @param n the root of the tree to find max. of.
 */
RBNODE find_subtree_max(RBNODE n)
{
    while (n->right)
        n = n->right;
    return n;
}

/**
 * Swaps the positions of two nodes
 */
void swap(RBNODE n, RBNODE m)
{
    RBNODE tmp = n;
    n = m;
    m = tmp;
}

/**
 * Finds the height of the given node 
 */
int find_subtree_height(RBNODE n)
{
    if (n == NULL)
    {
        return 0;
    }
    else
    {

        int ld = find_subtree_height(n->left);
        int rd = find_subtree_height(n->right);

        if (ld > rd)
            return (ld + 1);
        else
            return (rd + 1);
    }
}

int find_node_rank(RBNODE n)
{
    int cnt = 0;
    while (n)
    {
        if (n->color == BLACK)
        {
            cnt++;
        }
        n = n->left;
    }
    return cnt;
}

int find_subtree_size(RBNODE n) {
    if (n == NULL)
        return 0;

    int total = 1;

    if (n->left != NULL) {
        total += find_subtree_size(n->left);
    }

    if (n->right != NULL) {
        total += find_subtree_size(n->right);
    }

    return total;
}

// ////////////////////// ///////////////////////// ///////////////////////
// Insertion Helpers
// ////////////////////// ///////////////////////// ///////////////////////

/**
 * @brief Inserts {@code RBNODE } from the given root
 * @param root Pointer to root of insertion
 * @param n RBNODE being inserted
 * @param cmp function being used to recurse through the tree
 */
RBNODE insert(RBNODE root, RBNODE n, cmp_func_t cmp)
{
    insert_recursive(root, n, cmp);

    __repair_insert(n);

    root = n;
    while (parent(root) != NULL)
    {
        root = parent(root);
    }
    return root;
}

/**
 * @brief Recursive insertion to walk the tree
 * @param root root of insertion
 * @param n Node being inserted
 * @param cmp function being used to recurse through the tree
 */
void insert_recursive(RBNODE root, RBNODE n, cmp_func_t cmp)
{
    if (root != NULL)
    {
        if (cmp(n->key, root->key) < 0)
        {
            if (root->left != NULL)
            {
                insert_recursive(root->left, n, cmp);
                return;
            }
            else
            {
                root->left = n;
            }
        }
        else
        {
            if (root->right != NULL)
            {
                insert_recursive(root->right, n, cmp);
                return;
            }
            else
            {
                root->right = n;
            }
        }
    }

    n->parent = root;
    n->left = NULL;
    n->right = NULL;
    n->color = RED;
}

void __repair_insert(RBNODE n)
{

    if (parent(n) == NULL)
    {
        insert_case_1(n);
    }
    else if (parent(n)->color == BLACK)
    {
        return;
    }
    else if (uncle(n) != NULL && uncle(n)->color == RED)
    {
        insert_case_2(n);
    }
    else
    {
        insert_case_3(n);
    }
};

void insert_case_1(RBNODE n)
{
    n->color = BLACK;
};

void insert_case_2(RBNODE n)
{
    parent(n)->color = BLACK;
    uncle(n)->color = BLACK;
    grandparent(n)->color = RED;
    __repair_insert(grandparent(n));
};

void case_3_helper(RBNODE n)
{
    RBNODE p = parent(n);
    RBNODE g = grandparent(n);

    if (n == p->left)
    {
        rotate_right(g);
    }
    else
    {
        rotate_left(g);
    }

    p->color = BLACK;
    g->color = RED;
}

void insert_case_3(RBNODE n)
{
    RBNODE p = parent(n);
    RBNODE g = grandparent(n);

    if (n == p->right && p == g->left)
    {
        rotate_left(p);
        n = n->left;
    }
    else if (n == p->left && p == g->right)
    {
        rotate_right(p);
        n = n->right;
    }

    case_3_helper(n);
};

// ////////////////////// ///////////////////////// ///////////////////////
// Find Helpers
// ////////////////////// ///////////////////////// ///////////////////////

/**
 * @brief recursive find method
 * @param root root of search
 * @param key value to find
 * @param cmp method used to traverse the tree
 * @returns the node that matches key, NULL if key not found
 */
RBNODE find_node(RBNODE root, void *key, cmp_func_t cmp)
{
    if (root == NULL)
        return NULL;

    int cmp_val = cmp(root->key, key);

    if (cmp_val == 0)
        return root;
    else if (cmp_val < 0)
        return find_node(root->right, key, cmp);
    else
        return find_node(root->left, key, cmp);
}

// ////////////////////// ///////////////////////// ///////////////////////
// Delete Helpers
// ////////////////////// ///////////////////////// ///////////////////////

/**
 * @brief delete helper that replaces a node within a tree with its child
 * @param tree pointer to the tree
 * @param n node to be replaces
 * @param child node to replace n with
 */
void replace_child(RBTREE tree, RBNODE n, RBNODE child)
{

    RBNODE parent;

    parent = n->parent;

    if (child)
        child->parent = parent;

    if (parent)
    {
        if (parent->left == n)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }
    }
    else
    {
        tree->root = child;
        if (child)
            child->color = BLACK;
    }
}

void delete_one_child(RBTREE tree, RBNODE n)
{

    RBNODE child = n->left != NULL ? n->left : n->right;

    if (n->color == BLACK)
    {
        n->color = node_color(child);
        delete_case_1(tree, n);
    }
    replace_child(tree, n, child);
}

void delete_case_1(RBTREE tree, RBNODE n)
{
    if (n->parent != NULL)
    {
        delete_case_2(tree, n);
    }
}

void delete_case_2(RBTREE tree, RBNODE n)
{
    RBNODE s = sibling(n);

    if (s->color == RED)
    {
        n->parent->color = RED;
        s->color = BLACK;
        if (n == n->parent->left)
        {
            rotate_left(n->parent);
        }
        else
        {
            rotate_right(n->parent);
        }
    }
    delete_case_3(tree, n);
}

void delete_case_3(RBTREE tree, RBNODE n)
{
    RBNODE s = sibling(n);

    if ((n->parent->color == BLACK) &&
        (node_color(s) == BLACK) &&
        (node_color(s->left) == BLACK) &&
        (node_color(s->right) == BLACK))
    {
        s->color = RED;
        delete_case_1(tree, n->parent);
    }
    else
    {
        delete_case_4(tree, n);
    }
}

void delete_case_4(RBTREE tree, RBNODE n)
{
    RBNODE s = sibling(n);

    if ((n->parent->color == RED) &&
        (node_color(s) == BLACK) &&
        (node_color(s->left) == BLACK) &&
        (node_color(s->right) == BLACK))
    {
        s->color = RED;
        n->parent->color = BLACK;
    }
    else
    {
        delete_case_5(tree, n);
    }
}

void delete_case_5(RBTREE tree, RBNODE n)
{
    RBNODE s = sibling(n);

    if (s->color == BLACK)
    {
        if ((n == n->parent->left) &&
            (node_color(s->right) == BLACK) &&
            (node_color(s->left) == RED))
        {
            s->color = RED;
            s->left->color = BLACK;
            rotate_right(s);
        }
        else if ((n == n->parent->right) &&
                 (node_color(s->left) == BLACK) &&
                 (node_color(s->right) == RED))
        {
            s->color = RED;
            s->right->color = BLACK;
            rotate_left(s);
        }
    }
    delete_case_6(tree, n);
}

void delete_case_6(RBTREE tree, RBNODE n)
{
    RBNODE s = sibling(n);

    s->color = n->parent->color;
    n->parent->color = BLACK;

    if (n == n->parent->left)
    {
        s->right->color = BLACK;
        rotate_left(n->parent);
    }
    else
    {
        s->left->color = BLACK;
        rotate_right(n->parent);
    }
}
