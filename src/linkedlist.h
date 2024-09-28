#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct LinkedList LinkedList;
typedef struct LinkedListIterator LinkedListIterator;

LinkedList *linkedlist_new();
void linkedlist_add(LinkedList *list, void *item);
void linkedlist_add_all(LinkedList *list, LinkedList *addable);
void linkedlist_insert(LinkedList *list, size_t idx, void *item);
void *linkedlist_get(LinkedList *list,  size_t idx);
void *linkedlist_get_last(LinkedList *list);
void *linkedlist_remove(LinkedList *list, size_t idx);
//TODO
// void *linkedlist_remove_last(LinkedList *list);
//TODO
// LinkedList *linkedlist_reverse(LinkedList *list);
LinkedListIterator *linkedlist_iterator(LinkedList *list);
void *linkedlist_it_next(LinkedListIterator *iterator);
size_t linkedlist_it_i(LinkedListIterator *iterator);
size_t linkedlist_size(LinkedList *list);
//TODO
// void for_each(LinkedList *list, void (*callback)(void*));
void linkedlist_print(LinkedList *list, void (*printfn)(void*));
void linkedlist_free(LinkedList *list, bool items);

#endif
