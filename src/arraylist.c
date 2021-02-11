#include "arraylist.h"
#include <stdlib.h>
#include <glib.h>

#define INITIAL_CAP (10)
#define POINTER_SIZE (sizeof(void*))

typedef struct ArrayList {
  void **arr;
  size_t size;
  size_t cap;
  size_t cur;
} ArrayList;

ArrayList *new_arraylist() {
  ArrayList *list = malloc(sizeof(ArrayList));
  *list = ((ArrayList){.size = 0, .cap = INITIAL_CAP, .cur = 0 });
  list->arr = malloc(POINTER_SIZE * INITIAL_CAP);
  return list;
}


void _arraylist_free_func(void *ele) {
    free(ele);
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

void *arraylist_get(ArrayList *list, size_t i) {
    if(i >= list->size) {
        return NULL;
    }
    
    return list->arr[i];
}

void arraylist_add(ArrayList *list, void *elem) {
  if (list->size >= list->cap) {
    list->cap *= 1.5;
    list->arr = realloc(list->arr, list->cap * POINTER_SIZE);
  }

  // printf("ele: %lu\n", *(size_t *)elem);
  // printf("size: %lu\n", list->size);
  // printf("cap: %lu\n", list->cap);

  list->arr[list->size++] = elem;
}

void for_each(ArrayList *list, void (*callback)(void *item)) {
  for (size_t i = 0; i < list->size; i++) {
    callback(list->arr[i]);
  }
}

char *arraylist_next(ArrayList *list) {
    if(list->cur + 1 >= list->size) {
       return NULL; 
    }

    return list->arr[++list->cur];
}

char *arraylist_first(ArrayList *list) {
    if(list->size == 0) {
        return NULL;
    }

    list->cur = 0;
    return list->arr[list->cur];
}
