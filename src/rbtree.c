#include <rbtree.h>
#include <stdlib.h>

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


RBTREE rb_create(cmp_func_t cmp) {
    RBTREE tree = malloc(sizeof(struct rb_tree));
    assert(tree);

    tree->cmp = cmp;

    return tree;
}

//
// These are all the insertion helpers
void insert_case_1(RBNODE n);
void insert_case_2(RBNODE n);
void insert_case_3(RBNODE n);
void insert_case_4(RBNODE n);
void __repair_insert(RBNODE n);

//
// Theses do the actual insertion
RBNODE insert(RBNODE root, RBNODE n, cmp_func_t cmp);
void insert_recursive(RBNODE root, RBNODE n, cmp_func_t cmp);

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

//
//
// Removal helpers
void delete_case_1(RBNODE n);
void delete_case_2(RBNODE n);
void delete_case_3(RBNODE n);
void delete_case_4(RBNODE n);
void delete_case_5(RBNODE n);
void delete_case_6(RBNODE n);

void replace_node(RBNODE n, RBNODE other)
{
    other->parent = n->parent;
    if (n == n->parent->left)
    {
        n->parent->left = other;
    }
    else
    {
        n->parent->right = other;
    }
}

void delete_child(RBNODE n)
{
    // Assumes that n has, at most, one non-leaf child.
    RBNODE child = (n->right == NULL) ? n->left : n->right;
    assert(child);

    replace_node(n, child);

    if (n->color == BLACK)
    {
        if (child->color == RED)
        {
            child->color = BLACK;
        }
        else
        {
            delete_case_1(child);
        }
    }
    free(n);
}

void delete_case_1(RBNODE n)
{
    if (n->parent != NULL)
        delete_case_2(n);
}

void delete_case_2(RBNODE n)
{
    RBNODE s = get_sibling_node(n);

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

    delete_case_3(n);
}

void delete_case_3(RBNODE n)
{
    RBNODE s = get_sibling_node(n);

    if ((n->parent->color == BLACK) && (s->color == BLACK) && (s->left->color == BLACK) && (s->right->color == BLACK))
    {
        s->color = BLACK;
        delete_case_1(n->parent);
    }
    else
    {
        delete_case_4(n);
    }
}

void delete_case_4(RBNODE n)
{
    RBNODE s = get_sibling_node(n);

    if ((n->parent->color == RED) && (s->color == BLACK) && (s->left->color == BLACK) && (s->right->color == BLACK))
    {
        s->color = RED;
        n->parent->color = BLACK;
    }
    else
    {
        delete_case_5(n);
    }
}

void delete_case_5(RBNODE n)
{
    RBNODE s = get_sibling_node(n);

    if (s->color == BLACK)
    {
        if ((n == n->parent->left) && (s->right->color == BLACK) &&
            (s->left->color == RED))
        {
            s->color = RED;
            s->left->color = BLACK;
            rotate_right(s);
        }
        else if ((n == n->parent->right) && (s->left->color == BLACK) && (s->right->color == RED))
        {
            s->color = RED;
            s->right->color = BLACK;
            rotate_left(s);
        }
    }

    delete_case_6(n);
}

void delete_case_6(RBNODE n)
{
    RBNODE s = get_sibling_node(n);

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

//
// QUEUE
//
// Quick Queue definition for printing things in level order
//
////////////////////////////////////////////////////////////////

struct Queue {
    RBNODE data;
    struct Queue *next;
};

struct Queue *front = NULL;
struct Queue *rear = NULL;

RBNODE pop_front() {
    RBNODE data = NULL;
    data = front->data;
    return data;
}

int isempty() {
    if (front == NULL)
        return 1;
    else
        return 0;
}

void dequeue() {
    if (isempty())
        return;

    struct Queue *tmp = front;
    front = front->next;
    free(tmp);
}

void enqueue(RBNODE data) {
    struct Queue *tmp = (struct Queue *)malloc(sizeof(struct Queue));
    tmp->data = data;
    tmp->next = NULL;

    if (front == NULL && rear == NULL) {
        front = rear = tmp;
        return;
    }

    rear->next = tmp;
    rear = tmp;
}

void levelorder(RBNODE root, void(*func)(RBNODE)) {

    if (root == NULL)
        return;

    enqueue(root);

    while (!isempty()) {
        RBNODE curr = pop_front();
        func(curr);

        if (curr->left != NULL)
            enqueue(curr->left);

        if (curr->right != NULL)
            enqueue(curr->right);

        dequeue();
    }
}

void preorder(RBNODE n, void (*func)(RBNODE)) {
    if (n == NULL) {
        return;
    }

    func(n);

    if (n->left != NULL) {
        preorder(n->left, func);
    }

    if (n->right != NULL) {
        preorder(n->right, func);
    }
}

void postorder(RBNODE n, void(*func)(RBNODE)) {
    if (n == NULL) return;

    if (n->left != NULL) {
        postorder(n->left, func);
    }

    if (n->right != NULL) {
        postorder(n->right, func);
    }

    func(n);
}

void inorder(RBNODE n, void(*func)(RBNODE)) {
    if (n == NULL) return;

    if (n->left != NULL) {
        inorder(n->left, func);
    }

    func(n);

    if (n->right != NULL) {
        inorder(n->right, func);
    }
}

void print_tree(RBTREE tree, void(*func)(RBNODE)) {
    inorder(tree->root, func);
}
