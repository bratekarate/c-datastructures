#include <stddef.h>

typedef struct ArrayList ArrayList;
ArrayList *new_arraylist();
void arraylist_free(ArrayList *list);
void arraylist_free_all(ArrayList *list);
void arraylist_add(ArrayList *list, void *elem);
void arraylist_insert(ArrayList *list, size_t i, void *elem);
void *arraylist_get(ArrayList *list, size_t i);
void *arraylist_get_last(ArrayList *list);
void *arraylist_remove(ArrayList *list, size_t i);
void *arraylist_remove_last(ArrayList *list);
char *arraylist_it_next(ArrayList *list);
char *arraylist_it_first(ArrayList *list);
void for_each(ArrayList *list, void (*callback)(void*));
