#include <stdio.h>

typedef struct ArrayList ArrayList;

ArrayList *new_arraylist(size_t elem_size);
void arraylist_free(ArrayList *list);
void arraylist_free_all(ArrayList *list);
void arraylist_add(ArrayList *list, void *elem);
void *arraylist_get(ArrayList *list, size_t i);
char *arraylist_next(ArrayList *list);
char *arraylist_first(ArrayList *list);
void for_each(ArrayList *list, void (*callback)(void*));
