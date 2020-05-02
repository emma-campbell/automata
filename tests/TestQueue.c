#include <narwhal.h>
#include <queue.h>

TEST(QUEUE_CREATE) {
    QUEUE q = create_queue();
    ASSERT(q != NULL);
}

TEST(QUEUE_ENQUEUE) {
    QUEUE q = create_queue();
    enqueue(q, INT2VOIDP(5));

    ASSERT(dequeue(q) == INT2VOIDP(5));
}

TEST(QUEUE_ISEMPTY) {
    QUEUE q = create_queue();
    enqueue(q, INT2VOIDP(9));
    enqueue(q, INT2VOIDP(5));

    ASSERT(is_empty(q) == 0);
}