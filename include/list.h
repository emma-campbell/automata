/**
 * @file list.h
 * @author Emma Campbell
 * @date 2020-04-08
 * 
 */
#ifndef _LIST_h
#define _LIST_h

#include <stdlib.h>
#include <stdbool.h>

struct node
{
    void *data;
    struct node *next;
};

typedef struct node *Node;

struct list 
{
    int size;
    int (*cmp)(void *key1, void *key2);
    void (*destroy)(void *data);
    Node head;
    Node tail;
};

typedef struct list *List;

/**
 * @brief Create and allocate for new list object
 * @param destroy Freeing function for the stuff in the list
 * @returns new List object
 */
extern List list_create(void (*destroy)(void *data));

/**
 * @brief Delete the list object
 * @param l Pointer to the list
 */
extern void list_destroy(List l);

/**
 * @brief add a new element to the list
 * @param l pointer to the list
 * @param data pointer to the data
 */
extern void list_add(List l, void *data);

/**
 * @brief remove an element from the list
 * @param l pointer to the list
 * @param data pointer to data being removed
 */
extern void list_remove(List l, void *data);

/**
 * @brief does the list contain this element?
 * @param l pointer to the list
 * @param data pointer to data being removed
 */
extern bool list_contains(List l, void *data);

#endif // _LIST_h