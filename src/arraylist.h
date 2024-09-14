#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ArrayList ArrayList;
typedef struct ArrayListIterator ArrayListIterator;

ArrayList *arraylist_new();
void arraylist_add(ArrayList *list, void *elem);
void arraylist_add_all(ArrayList *list, ArrayList *addable);
void arraylist_add_i(ArrayList *list, intmax_t val, size_t size);
void arraylist_add_f(ArrayList *list, double val, size_t size);
void arraylist_insert(ArrayList *list, size_t i, void *elem);
void *arraylist_get(ArrayList *list, size_t i);
void *arraylist_get_last(ArrayList *list);
void *arraylist_remove(ArrayList *list, size_t i);
void *arraylist_remove_last(ArrayList *list);
ArrayList *arraylist_reverse(ArrayList *list);
ArrayListIterator *arraylist_iterator(ArrayList *list);
void *arraylist_it_next(ArrayListIterator *iterator);
size_t arraylist_it_i(ArrayListIterator *iterator);
size_t arraylist_size(ArrayList *list);
void arraylist_foreach(ArrayList *list, void (*callback)(void*));
void arraylist_print(ArrayList *list, void (*printfn)(void*));
void arraylist_free(ArrayList *list, bool items);

#endif
