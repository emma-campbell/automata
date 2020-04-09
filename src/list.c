#include <list.h>

Node create_node(void *data);

// ///////////////////////////////////////////////////////////
// Public Functions
// ///////////////////////////////////////////////////////////

List list_create(void (*destroy)(void *data)) 
{
    List l = malloc(sizeof(struct list));

    if (l == NULL) {
        return NULL;
    }

    l->size = 0;
    l->destroy = destroy;
    l->head = NULL;
    l->tail = NULL;

    return l;
}

void list_add(List l, void *data) 
{
    Node tmp, p;
    tmp = create_node(data);
    
    if (l->head == NULL)
    {
        l->head = tmp;
    }
    else
    {
        p = l->head;

        while (p->next != NULL)
        {
            p = p->next;
        }

        p->next = tmp;
    }
    l->size++;
}

void list_remove(List l, void*data)
{
    if (l->head == NULL) {
        return;
    }

    Node curr = l->head;
    Node prev = curr;

    while (curr != NULL) {
        if (curr->data == data) {
            prev->next = curr->next;
            if (curr == l->head)
                l->head = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    l->size--;
}

bool list_contains(List l, void*data) 
{
    if (l->head == NULL) return false;

    Node curr = l->head;

    while (curr != NULL)
    {
        if (curr->data == data)
        {
            return true;
        }

        curr = curr->next;
    }

    return false;
}

void list_destroy(List l) 
{
    Node curr = l->head;
    Node next = curr;

    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    free(l);
}

// ////////////////////////////////////////////////////////////
// Private Functions
// ////////////////////////////////////////////////////////////

Node create_node(void *data)
{
    Node n = malloc(sizeof(struct node));

    if (n == NULL)
        return NULL;

    n->data = data;
    n->next = NULL;

    return n;
}