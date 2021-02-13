#include "arraylist.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAP (10)
#define POINTER_SIZE (sizeof(void *))

ArrayList *new_arraylist();
void arraylist_add(ArrayList *list, void *elem);
void arraylist_insert(ArrayList *list, size_t i, void *elem);
void *arraylist_get(ArrayList *list, size_t i);
void *arraylist_get_last(ArrayList *list);
void *arraylist_remove(ArrayList *list, size_t i);
void *arraylist_remove_last(ArrayList *list);
void *arraylist_it_first(ArrayList *list);
void *arraylist_it_next(ArrayList *list);
void for_each(ArrayList *list, void (*callback)(void *item));
ArrayList *arraylist_reverse(ArrayList *list);
void arraylist_print(ArrayList *list, void printfn(void*));
void arraylist_free_all(ArrayList *list);
void arraylist_free(ArrayList *list);

void _arraylist_free_func(void *ele);
void _grow_if_exceeds(ArrayList *list);
void _shrink_if_small(ArrayList *list);

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
  arraylist_insert(list, list->size, elem);
}

void arraylist_insert(ArrayList *list, size_t index, void *elem) {
  _grow_if_exceeds(list);
  if (list->size > 0) {
    for (size_t i = list->size - 1; i >= index; i--) {
      list->arr[i + 1] = list->arr[i];
    }
  }

  list->arr[index] = elem;
  list->size++;
}

void *arraylist_get(ArrayList *list, size_t i) {
  if (i >= list->size) {
    return NULL;
  }

  return list->arr[i];
}

void *arraylist_get_last(ArrayList *list) {
  return list->size != 0 ? list->arr[list->size - 1] : NULL;
}

void *arraylist_remove(ArrayList *list, size_t index) {
  if (list->size == 0 || index >= list->size) {
    return NULL;
  }

  char *elem = list->arr[index];

  for (size_t i = index; i < list->size; i++) {
    list->arr[i] = list->arr[i + 1];
  }

  list->size--;
  _shrink_if_small(list);

  return elem;
}

void *arraylist_remove_last(ArrayList *list) {
  return arraylist_remove(list, list->size - 1);
}

void *arraylist_it_first(ArrayList *list) {
  if (list->size == 0) {
    return NULL;
  }

  list->cur = 0;
  return list->arr[list->cur];
}

void *arraylist_it_next(ArrayList *list) {
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

ArrayList *arraylist_reverse(ArrayList *list) {
  int l, r;
  for (l = 0, r = list->size - 1; l < r; l++, r--) {
    void *tmp = list->arr[l];
    list->arr[l] = list->arr[r];
    list->arr[r] = tmp;
  }
}

void arraylist_print(ArrayList *list, void printfn(void*)) {
  printf("[ ");
  void *next = arraylist_it_first(list);
  do {
    printfn(next);    
    printf(", ");
  } while((next = arraylist_it_next(list)) != NULL);

  printf("]\n");
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

void _grow_if_exceeds(ArrayList *list) {
  if (list->size >= list->cap) {
    list->cap *= 1.5;
    list->arr = realloc(list->arr, list->cap * POINTER_SIZE);
  }
}

void _shrink_if_small(ArrayList *list) {
  if (list->size * 2 < list->cap) {
    list->cap = list->size * 1.5;
    list->arr = realloc(list->arr, list->cap * POINTER_SIZE);
  }
}
