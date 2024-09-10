#include <stddef.h>
#include <stdbool.h>

typedef struct LinkedList LinkedList;
LinkedList *linkedlist_new();
void linkedlist_add(LinkedList *list, void *item);
void linkedlist_add_all(LinkedList *list, LinkedList *addable);
//TODO
//void linkedlist_insert(LinkedList *list, size_t i, void *elem);
void *linkedlist_get(LinkedList *list, const size_t index);
//TODO
//void *linkedlist_get_last(LinkedList *list);
void *linkedlist_remove(LinkedList *list, const size_t index);
//TODO
// void *linkedlist_remove_last(LinkedList *list);
//TODO
// LinkedList *linkedlist_reverse(LinkedList *list);
//TODO
// void *linkelist_it_next(LinkedList *list);
//TODO
// void *linkedlist_it_first(LinkedList *list);
size_t linkedlist_size(LinkedList *list);
//TODO
// void for_each(LinkedList *list, void (*callback)(void*));
void linkedlist_print(LinkedList *list, void (*printfn)(void*));
void linkedlist_free(LinkedList *list, bool items);
// TODO
// void linkedlist_free_all(LinkedList *list);
