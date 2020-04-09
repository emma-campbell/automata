#include <narwhal.h>
#include <list.h>

TEST (LIST_CREATE) {
    List l = list_create(free);
    ASSERT(l != NULL, "Unable to allocate storage");
}

TEST (LIST_ADD) {
    List l = list_create(free);

    list_add(l, (void *)1);
    list_add(l, (void *)2);
    list_add(l, (void *)3);
    list_add(l, (void *)4);

    ASSERT(list_contains(l, (void*) 2) == 1);
    ASSERT(l->size == 4);
}

TEST(LIST_REMOVE) {
    List l = list_create(free);

    list_add(l, (void *)1);
    list_add(l, (void *)2);
    list_add(l, (void *)3);
    list_add(l, (void *)4);

    list_remove(l, (void *)2);

    ASSERT(list_contains(l, (void *)2) == 0);
}

TEST (LIST_CONTAINS) {
    List l = list_create(free);

    list_add(l, (void *)"snuffalufagus");
    list_add(l, (void *)"snorts");

    ASSERT(list_contains(l, (void *)"snuffalufagus") == 1);
    ASSERT(list_contains(l, (void *)"word") == 0);
}