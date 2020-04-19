#include <queue.h>

// declare private functions
QNODE create_node(void *data);

////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////

QUEUE create_queue() {
    QUEUE q = malloc(sizeof(struct queue));
    
    if (q == NULL)
        return NULL;

    q->front = NULL;
    q->rear = NULL;
    return q;
}

void *pop_front(QUEUE q) {
    void *data = NULL;
    data = q->front->data;
    return data;
}

void enqueue(QUEUE q, void*data) {
    QNODE tmp = create_node(data);

    if (q->front == NULL && q->rear == NULL) {
        q->front = q->rear = tmp;
        return;
    }

    q->rear->next = tmp;
    q->rear = tmp;
}

void *dequeue(QUEUE q) {
    
    void *data = NULL;

    if (is_empty(q))
        return NULL;

    QNODE tmp = q->front;
    q->front = q->front->next;

    data = tmp->data;
    free(tmp);

    return data;
}

int is_empty(QUEUE q) {
    if (q->front == NULL)
        return 1;
    else
        return 0;
}

////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////

QNODE create_node(void*data) {
    QNODE node = malloc(sizeof(struct queue_t));

    if (!node)
        return NULL;

    node->data = data;
    node->next = NULL;
    return node;
}