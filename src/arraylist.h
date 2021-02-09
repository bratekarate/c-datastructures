#include <stdio.h>

typedef struct ArrayList ArrayList;

ArrayList *new_arraylist(size_t elem_size);
void destroy_arraylist(ArrayList *list);
void add(ArrayList *list, void *elem);
void for_each(ArrayList *list, void (*callback)());
