#ifndef _QUEUE_h
#define _QUEUE_h

#include <common.h>

struct queue_t {
    void *data;
    struct queue_t *next;
};

typedef struct queue_t *QNODE;

struct queue {
    QNODE front;
    QNODE rear;
};

typedef struct queue *QUEUE;

extern QUEUE create_queue();

extern void *pop_front(QUEUE q);
extern void enqueue(QUEUE q, void *data);
extern void *dequeue(QUEUE q);
extern int is_empty(QUEUE q);

#endif //_QUEUE_h