#include "arraylist.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAP (10)
#define POINTER_SIZE (sizeof(void *))
#define ARRAY_LIST_ALIGNED (32)
#define ARRAY_LIST_ITERATOR_ALIGNED (16)
#define ARRAY_LIST_GROW_FACTOR (1.5)

void elem_free_func(void *ele);
size_t grow_if_exceeds(ArrayList *list);
size_t shrink_if_small(ArrayList *list);

struct ArrayList {
  void **arr;
  size_t size;
  size_t cap;
} __attribute__((aligned(ARRAY_LIST_ALIGNED)));

struct ArrayListIterator {
  ArrayList *list;
  size_t i;
} __attribute__((aligned(ARRAY_LIST_ITERATOR_ALIGNED)));

ArrayList *arraylist_new() {
  ArrayList *list = malloc(sizeof(ArrayList));
  *list = ((ArrayList){.size = 0, .cap = INITIAL_CAP});
  list->arr = (void**)malloc(POINTER_SIZE * INITIAL_CAP);
  return list;
}

size_t arraylist_add(ArrayList *list, void *elem) {
  return arraylist_insert(list, list->size, elem);
}

size_t arraylist_add_all(ArrayList *list, ArrayList *addable) {
  ArrayListIterator *iter = arraylist_iterator(addable);
  void *next = NULL;
  while ((next = arraylist_it_next(iter)) != NULL) {
    size_t res = arraylist_add(list, next);
    if (res < 0) {
      return res;
    }
  }
  free(iter);
  iter = NULL;
  return list->size;
}

size_t arraylist_add_i(ArrayList *list, intmax_t val, size_t size) {
  intmax_t *elem = malloc(size);
  *elem = val;
  return arraylist_insert(list, list->size, elem);
}

size_t arraylist_add_f(ArrayList *list, double val, size_t size) {
  double *elem = malloc(size);
  *elem = val;
  return arraylist_insert(list, list->size, elem);
}

size_t arraylist_insert(ArrayList *list, size_t index, void *elem) {
  size_t res = grow_if_exceeds(list);
  if (res < 0) {
    return -1;
  }
  if (list->size > 0) {
    for (size_t i = list->size - 1; i >= index; i--) {
      list->arr[i + 1] = list->arr[i];
    }
  }

  list->arr[index] = elem;
  list->size++;
  return list->size;
}

void *arraylist_get(ArrayList *list, size_t idx) {
  if (idx >= list->size) {
    return NULL;
  }

  return list->arr[idx];
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
  shrink_if_small(list);

  return elem;
}

void *arraylist_remove_last(ArrayList *list) {
  return arraylist_remove(list, list->size - 1);
}

ArrayListIterator *arraylist_iterator(ArrayList *list) {
  if (list->size == 0) {
    return NULL;
  }

  ArrayListIterator *iter = malloc(sizeof(ArrayListIterator));
  *iter = (ArrayListIterator){.i = 0, .list = list};

  return iter;
}

size_t arraylist_it_i(ArrayListIterator *iter) { return iter->i; }

void *arraylist_it_next(ArrayListIterator *iter) {
  if (iter->i >= iter->list->size) {
    return NULL;
  }

  return iter->list->arr[iter->i++];
}

size_t arraylist_size(ArrayList *list) { return list->size; }

void arraylist_foreach(ArrayList *list, void (*callback)(void *item)) {
  for (size_t i = 0; i < list->size; i++) {
    callback(list->arr[i]);
  }
}

ArrayList *arraylist_reverse(ArrayList *list) {
  for (size_t l = 0, r = list->size - 1; l < r; l++, r--) {
    void *tmp = list->arr[l];
    list->arr[l] = list->arr[r];
    list->arr[r] = tmp;
  }
  return list;
}

void arraylist_print(ArrayList *list, void (*printfn)(void *)) {
  printf("[ ");
  ArrayListIterator *iter = arraylist_iterator(list);
  void *next = NULL;
  while ((next = arraylist_it_next(iter)) != NULL) {
    if (arraylist_it_i(iter) != 1) {
      printf(", ");
    }
    printfn(next);
  }
  free(iter);
  iter = NULL;
  printf(" ]\n");
}

void arraylist_free(ArrayList *list, bool items) {
  if (items) {
    arraylist_foreach(list, elem_free_func);
  }
  free((void*)list->arr);
  list->arr = NULL;
  free(list);
}

void elem_free_func(void *ele) { free(ele); }

size_t grow_if_exceeds(ArrayList *list) {
  if (list->size >= list->cap) {
    list->cap = (size_t)((double)list->cap * ARRAY_LIST_GROW_FACTOR);
    void **newarr = (void**)realloc((void*)list->arr, list->cap * POINTER_SIZE);
    if (newarr == NULL) {
      return -1;
    }
    list->arr = newarr;
  }
  return list->cap;
}

size_t shrink_if_small(ArrayList *list) {
  if (list->size * 2 < list->cap) {
    list->cap = (size_t)((double)list->size / ARRAY_LIST_GROW_FACTOR);
    void **newarr = (void**)realloc((void*)list->arr, list->cap * POINTER_SIZE);
    if (newarr == NULL) {
      return -1;
    }
    list->arr = newarr;
  }
  return list->cap;
}
