#include "arraylist.h"
#include <stdlib.h>

#define INITIAL_CAP (10)

typedef struct ArrayList {
  void **arr;
  size_t size;
  size_t cap;
  size_t elem_size;
} ArrayList;

ArrayList *new_arraylist(size_t elem_size) {
  ArrayList *list = malloc(sizeof(ArrayList));
  *list = ((ArrayList){.size = 0, .cap = INITIAL_CAP, .elem_size = elem_size});
  list->arr = malloc(elem_size * INITIAL_CAP);
  return list;
}

void destroy_arraylist(ArrayList *list) {
  free(list->arr);
  list->arr = NULL;
  free(list);
}

void add(ArrayList *list, void *elem) {
  if (list->size >= list->cap) {
    list->cap *= 1.5;
    list->arr = realloc(list->arr, list->cap * list->elem_size);
  }

  list->arr[list->size++] = elem;
}

void for_each(ArrayList *list, void (*callback)()) {
  for (size_t i = 0; i < list->size; i++) {
    callback(list->arr[i]);
  }
}
