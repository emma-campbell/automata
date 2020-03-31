#include <rbtree.h>
#include <stdlib.h>

#include <stdio.h>

// Node Helpers
//
// NOTE -- All these functions are hidden to the user
RBNODE node_create(void *key)
{
    RBNODE n = malloc(sizeof(struct rb_node));
    assert(n != NULL);

    n->key = key;
    n->color = RED;
    return n;
};

// return the parent node
RBNODE get_parent_node(RBNODE n)
{
    return n == NULL ? NULL : n->parent;
};

// return the grandparent node
RBNODE get_grand_parent_node(RBNODE n)
{
    return get_parent_node(get_parent_node(n));
};

//
RBNODE get_sibling_node(RBNODE n)
{
    RBNODE p = get_parent_node(n);

    if (p == NULL)
        return NULL;

    if (n == p->left)
        return p->right;
    else
        return p->left;
}

//
RBNODE get_uncle_node(RBNODE n)
{
    RBNODE p = get_parent_node(n);
    return get_sibling_node(p);
}

/**
 * Rotates the passed in node to the left
 */
void rotate_left(RBNODE n)
{
    RBNODE nnew = n->right;
    RBNODE p = get_parent_node(n);

    assert(nnew != NULL);

    n->right = nnew->left;
    nnew->left = n;
    n->parent = nnew;

    if (n->right != NULL)
        n->right->parent = n;

    if (p != NULL)
    {
        if (n == p->left)
        {
            p->left = nnew;
        }
        else if (n == p->right)
        {
            p->right = nnew;
        }
    }
    nnew->parent = p;
}

void rotate_right(RBNODE n)
{
    RBNODE nnew = n->left;
    RBNODE p = get_parent_node(n);

    assert(nnew != NULL);

    n->left = nnew->right;
    nnew->right = n;
    n->parent = nnew;

    if (n->left != NULL)
        n->left->parent = n;

    if (p != NULL)
    {
        if (n == p->left)
        {
            p->left = nnew;
        }
        else if (n == p->right)
        {
            p->right = nnew;
        }
    }

    nnew->parent = p;
}

RBTREE rb_create(cmp_func_t cmp)
{
    RBTREE tree = malloc(sizeof(struct rb_tree));
    assert(tree);

    tree->cmp = cmp;

    return tree;
}

void free_node(RBNODE n)
{
    free(n);
}

void rb_destroy(RBTREE tree)
{
    RBNODE tmp = tree->root;
    postorder(tmp, free_node);
    free(tree);
}

//
// Declaring the insertion helpers
void insert_case_1(RBNODE n);
void insert_case_2(RBNODE n);
void insert_case_3(RBNODE n);
void insert_case_4(RBNODE n);
void __repair_insert(RBNODE n);

//
// These do the insertions from a root node
RBNODE insert(RBNODE root, RBNODE n, cmp_func_t cmp);
void insert_recursive(RBNODE root, RBNODE n, cmp_func_t cmp);

//
// All this function does wrap `insert` so that you can call it just
// using the tree structure
int rb_insert(RBTREE tree, void *key)
{
    RBNODE new_node = node_create(key);
    tree->root = insert(tree->root, new_node, tree->cmp);
    return 1;
};

RBNODE insert(RBNODE root, RBNODE n, cmp_func_t cmp)
{
    insert_recursive(root, n, cmp);

    __repair_insert(n);

    root = n;
    while (get_parent_node(root) != NULL)
    {
        root = get_parent_node(root);
    }
    return root;
}

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

    if (get_parent_node(n) == NULL)
    {
        insert_case_1(n);
    }
    else if (get_parent_node(n)->color == BLACK)
    {
        return;
    }
    else if (get_uncle_node(n) != NULL && get_uncle_node(n)->color == RED)
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
    get_parent_node(n)->color = BLACK;
    get_uncle_node(n)->color = BLACK;
    get_grand_parent_node(n)->color = RED;
    __repair_insert(get_grand_parent_node(n));
};

void case_3_helper(RBNODE n)
{
    RBNODE p = get_parent_node(n);
    RBNODE g = get_grand_parent_node(n);

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
    RBNODE p = get_parent_node(n);
    RBNODE g = get_grand_parent_node(n);

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

RBNODE rb_find(RBTREE tree, void *key)
{
    return find_node(tree->root, key, tree->cmp);
}

// void rb_remove(RBTREE t, void *key)
// {
//     return;
// }

//
// QUEUE
//
// Quick Queue definition for printing things in level order
//
////////////////////////////////////////////////////////////////

struct Queue
{
    RBNODE data;
    struct Queue *next;
};

struct Queue *front = NULL;
struct Queue *rear = NULL;

RBNODE pop_front()
{
    RBNODE data = NULL;
    data = front->data;
    return data;
}

int isempty()
{
    if (front == NULL)
        return 1;
    else
        return 0;
}

void dequeue()
{
    if (isempty())
        return;

    struct Queue *tmp = front;
    front = front->next;
    free(tmp);
}

void enqueue(RBNODE data)
{
    struct Queue *tmp = (struct Queue *)malloc(sizeof(struct Queue));
    tmp->data = data;
    tmp->next = NULL;

    if (front == NULL && rear == NULL)
    {
        front = rear = tmp;
        return;
    }

    rear->next = tmp;
    rear = tmp;
}

void levelorder(RBNODE root, void (*func)(RBNODE))
{

    if (root == NULL)
        return;

    enqueue(root);

    while (!isempty())
    {
        RBNODE curr = pop_front();
        func(curr);

        if (curr->left != NULL)
            enqueue(curr->left);

        if (curr->right != NULL)
            enqueue(curr->right);

        dequeue();
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

//
// See https://www.cs.cmu.edu/~guyb/papers/BFS16.pdf for more on
// joining red black trees (as well as other balancing trees).
//

// void rb_join_right() {}