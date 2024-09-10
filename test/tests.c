#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../src/dastruct.h"
// TODO: duplice include in .c and .h file best practice?

#define FUNC_DEF(func) {func, #func},
#define FUNC_ARRAY_SIZE (sizeof(func_array) / sizeof(func_pointer_t))

void test_1();
void test_linked_list();
void print(void *i);
char *find(ArrayList *list, char *ele);
int no_digits(size_t nu);

typedef struct {
  void (*func)(void);
  const char *name;
} func_pointer_t;

func_pointer_t func_array[] = {
    FUNC_DEF(test_1)
    FUNC_DEF(test_linked_list)
};

int main() {
  for (size_t i = 0; i < FUNC_ARRAY_SIZE; i++) {
    printf("Running test '%s'...\n", func_array[i].name);
    func_array[i].func();
    printf("Success.\n");
  }
}

void test_1() {
  ArrayList *l = arraylist_new();

  for (size_t i = 0; i < 9; i++) {
    int size = no_digits(i) + 1;
    char *elem = malloc(size * sizeof(char));
    snprintf(elem, size, "%lu", i);
    arraylist_add(l, elem);
  }

  ArrayList *l2 = arraylist_new();
  for(size_t i = 500; i < 500 + arraylist_size(l); i++) {
    int size = no_digits(i) + 1;
    char *elem = malloc(size * sizeof(char));
    snprintf(elem, size, "%lu", i);
    printf("%s\n", elem);
    arraylist_add(l2, elem);
  }

  // TODO: causes memory issues later on?
  arraylist_add_all(l, l2);

  arraylist_free(l2, false);

  char *test = "test";
  char *testm = malloc((strlen(test) - 1) * sizeof(char));
  strcpy(testm, test);
  arraylist_insert(l, 2, testm);

  char *removed = (char*) arraylist_remove(l, 1);
  printf("removed: %s\n", removed);
  char *last = (char*) arraylist_remove_last(l);
  printf("removed last: %s\n", last);

  arraylist_print(l, print);
  arraylist_reverse(l);
  arraylist_print(l, print);
  
  printf("cur lst: %s\n", (char*) arraylist_get_last(l));
  printf("cur fst: %s\n", (char *)arraylist_get(l, 0));
  printf("find elem: %s\n", find(l, "test"));

  arraylist_free(l, true);

  l = NULL;
  testm = NULL;
  removed = NULL;
  last = NULL;
}

void test_linked_list() {
  LinkedList *list = linkedlist_new();

  for(size_t i = 0; i < 15; i++) {
    int size = no_digits(i) + 1;
    char *elem = malloc(size * sizeof(char));
    snprintf(elem, size, "%zu", i);
    linkedlist_add(list, elem);
  }

  linkedlist_print(list, print);

  LinkedList *list2 = linkedlist_new();

  for(size_t i = 500; i < 500 + linkedlist_size(list); i++) {
    int size = no_digits(i) + 1;
    // fprintf(stderr, "%lu\t%d\n", i, n_digits);
    char *elem = malloc(size * sizeof(char));
    snprintf(elem, size, "%lu", i);
    linkedlist_add(list2, elem);
  }

  linkedlist_print(list2, print);

  linkedlist_add_all(list, list2);

  linkedlist_print(list, print);
  printf("list[%d] = %d\nremove %d.\n", 1, 1, *(int*)linkedlist_remove(list, 1));
  linkedlist_print(list, print);
  printf("list[%d] = %d\n", 1, *(int*)linkedlist_get(list, 1));
  printf("list[0] = %d\nremove 0.\n", *(int*)linkedlist_remove(list, 0));
  linkedlist_print(list, print);
  printf("list[0] = %d\n", *(int*)linkedlist_get(list, 0));

  linkedlist_free(list, true);
  list = NULL;
}

void free_func(void *ele) {
    free(ele);
}

char *find(ArrayList *list, char *ele) {
  char *next = arraylist_it_first(list);
  do {
    if (!strcmp(next, ele)) {
      return next;
    }
  } while ((next = arraylist_it_next(list)) != NULL);

  return NULL;
}

void print(void *i) { printf("%s", (char *)i); }

int no_digits(size_t nu) {
  if (nu == 0) {
    return 1;
  }

  int c;
  for (c = 0; nu != 0; c++) {
    nu /= 10;
  }
  return c;
}
