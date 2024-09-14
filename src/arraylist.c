#include "arraylist.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAP (10)
#define POINTER_SIZE (sizeof(void *))

void elem_free_func(void *ele);
void grow_if_exceeds(ArrayList *list);
void shrink_if_small(ArrayList *list);

struct ArrayList {
  void **arr;
  size_t size;
  size_t cap;
};

struct ArrayListIterator {
  ArrayList *list;
  size_t i;
};

ArrayList *arraylist_new() {
  ArrayList *list = malloc(sizeof(ArrayList));
  *list = ((ArrayList){.size = 0, .cap = INITIAL_CAP});
  list->arr = malloc(POINTER_SIZE * INITIAL_CAP);
  return list;
}

void arraylist_add(ArrayList *list, void *elem) {
  arraylist_insert(list, list->size, elem);
}

void arraylist_add_all(ArrayList *list, ArrayList *addable) {
  ArrayListIterator *it = arraylist_iterator(addable);
  void *next;
  while ((next = arraylist_it_next(it)) != NULL) {
    arraylist_add(list, next);
  }
}

void arraylist_add_i(ArrayList *list, intmax_t val, size_t size) {
  intmax_t *elem = malloc(size);
  *elem = val;
  arraylist_insert(list, list->size, elem);
}

void arraylist_add_f(ArrayList *list, double val, size_t size) {
  double *elem = malloc(size);
  *elem = val;
  arraylist_insert(list, list->size, elem);
}

void arraylist_insert(ArrayList *list, size_t index, void *elem) {
  grow_if_exceeds(list);
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

  ArrayListIterator *it = malloc(sizeof(ArrayListIterator));
  *it = (ArrayListIterator){.i = 0, .list = list};

  return it;
}

size_t arraylist_it_i(ArrayListIterator *it) { return it->i; }

void *arraylist_it_next(ArrayListIterator *it) {
  if (it->i >= it->list->size) {
    return NULL;
  }

  return it->list->arr[it->i++];
}

size_t arraylist_size(ArrayList *list) { return list->size; }

void arraylist_foreach(ArrayList *list, void (*callback)(void *item)) {
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
  return list;
}

void arraylist_print(ArrayList *list, void (*printfn)(void *)) {
  printf("[ ");
  ArrayListIterator *it = arraylist_iterator(list);
  void *next;
  while ((next = arraylist_it_next(it)) != NULL) {
    if (arraylist_it_i(it) != 1) {
      printf(", ");
    }
    printfn(next);
  }
  printf(" ]\n");
}

void arraylist_free(ArrayList *list, bool items) {
  if (items) {
    arraylist_foreach(list, elem_free_func);
  }
  free(list->arr);
  list->arr = NULL;
  free(list);
}

void elem_free_func(void *ele) { free(ele); }

void grow_if_exceeds(ArrayList *list) {
  if (list->size >= list->cap) {
    list->cap *= 1.5;
    list->arr = realloc(list->arr, list->cap * POINTER_SIZE);
  }
}

void shrink_if_small(ArrayList *list) {
  if (list->size * 2 < list->cap) {
    list->cap = list->size * 1.5;
    list->arr = realloc(list->arr, list->cap * POINTER_SIZE);
  }
}
