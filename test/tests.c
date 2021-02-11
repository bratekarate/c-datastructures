#include "../src/arraylist.h"
#include <glib.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define FUNC_DEF(func) {func, #func},
#define FUNC_ARRAY_SIZE (sizeof(func_array) / sizeof(func_pointer_t))

void test_1();
void print(void *i);
void free_func(void *i);
char *find(ArrayList *list, char *ele);
int no_digits(size_t nu);

typedef struct {
  void (*func)(void);
  const char *name;
} func_pointer_t;

func_pointer_t func_array[] = {FUNC_DEF(test_1)};

int main() {
  for (size_t i = 0; i < FUNC_ARRAY_SIZE; i++) {
    printf("Running test '%s'...\n", func_array[i].name);
    func_array[i].func();
    printf("Success.\n");
  }
}

void test_1() {
  ArrayList *l = new_arraylist(sizeof(size_t));
  // GList *gl = NULL;

  for (size_t i = 0; i < 9999; i++) {
    // printf("adding ele\n");
    int size = no_digits(i) + 1;
    // printf("%lu\t%d\n", i, n_digits);
    char *elem = malloc(size * sizeof(char));
    snprintf(elem, size, "%lu", i);
    // gl = g_list_append(gl, elem);
    arraylist_add(l, elem);
  }

  for_each(l, print);
  // g_list_foreach(gl, print, NULL);

  // printf("%s\n", (char *)arraylist_get(l, 0));
  // printf("%s\n", find(l, "187"));

  arraylist_free_all(l);
  // g_list_free_full(gl, free_func);
}

void free_func(void *ele) {
    free(ele);
}

char *find(ArrayList *list, char *ele) {
  char *next = arraylist_first(list);
  do {
    if (!strcmp(next, ele)) {
      return next;
    }
  } while ((next = arraylist_next(list)) != NULL);

  return NULL;
}

void print(void *i) { printf("%s\n", (char *)i); }

int no_digits(size_t nu) {
  int c;
  for (c = 0; nu != 0; c++) {
    nu /= 10;
  }
  return c;
}
