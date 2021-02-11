#include "arraylist.h"
#include <glib.h>
#include <stdlib.h>

#define INITIAL_CAP (10)
#define POINTER_SIZE (sizeof(void *))

ArrayList *new_arraylist();
void arraylist_add(ArrayList *list, void *elem);
void *arraylist_get(ArrayList *list, size_t i);
char *arraylist_first(ArrayList *list);
char *arraylist_next(ArrayList *list);
void for_each(ArrayList *list, void (*callback)(void *item));
void arraylist_free_all(ArrayList *list);
void arraylist_free(ArrayList *list);
void _arraylist_free_func(void *ele);

typedef struct ArrayList {
  void **arr;
  size_t size;
  size_t cap;
  size_t cur;
} ArrayList;

ArrayList *new_arraylist() {
  ArrayList *list = malloc(sizeof(ArrayList));
  *list = ((ArrayList){.size = 0, .cap = INITIAL_CAP, .cur = 0});
  list->arr = malloc(POINTER_SIZE * INITIAL_CAP);
  return list;
}

void arraylist_add(ArrayList *list, void *elem) {
  if (list->size >= list->cap) {
    list->cap *= 1.5;
    list->arr = realloc(list->arr, list->cap * POINTER_SIZE);
  }

  list->arr[list->size++] = elem;
}

void *arraylist_get(ArrayList *list, size_t i) {
  if (i >= list->size) {
    return NULL;
  }

  return list->arr[i];
}

char *arraylist_first(ArrayList *list) {
  if (list->size == 0) {
    return NULL;
  }

  list->cur = 0;
  return list->arr[list->cur];
}

char *arraylist_next(ArrayList *list) {
  if (list->cur + 1 >= list->size) {
    return NULL;
  }

  return list->arr[++list->cur];
}

void for_each(ArrayList *list, void (*callback)(void *item)) {
  for (size_t i = 0; i < list->size; i++) {
    callback(list->arr[i]);
  }
}

void arraylist_free_all(ArrayList *list) {
  for_each(list, _arraylist_free_func);
  arraylist_free(list);
}

void arraylist_free(ArrayList *list) {
  free(list->arr);
  list->arr = NULL;
  free(list);
}

void _arraylist_free_func(void *ele) { free(ele); }
