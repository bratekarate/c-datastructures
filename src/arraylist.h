#include <stddef.h>

typedef struct ArrayList ArrayList;
ArrayList *arraylist_new();
void arraylist_add(ArrayList *list, void *elem);
//TODO
//void arraylist_add_all(ArrayList *list, void *elem);
void arraylist_insert(ArrayList *list, size_t i, void *elem);
void *arraylist_get(ArrayList *list, size_t i);
void *arraylist_get_last(ArrayList *list);
void *arraylist_remove(ArrayList *list, size_t i);
void *arraylist_remove_last(ArrayList *list);
ArrayList *arraylist_reverse(ArrayList *list);
void *arraylist_it_next(ArrayList *list);
void *arraylist_it_first(ArrayList *list);
// TODO
// size_t arraylist_size(ArrayList *list);
void arraylist_foreach(ArrayList *list, void (*callback)(void*));
void arraylist_print(ArrayList *list, void (*printfn)(void*));
void arraylist_free(ArrayList *list);
void arraylist_free_all(ArrayList *list);
