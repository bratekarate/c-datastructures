#include "../src/arraylist.h"
#include <stdlib.h>
#include <limits.h>
#include <glib.h>
#include <string.h>

#define FUNC_DEF(func) {func, #func},
#define FUNC_ARRAY_SIZE (sizeof(func_array) / sizeof(func_pointer_t))

void test_1();
void print(void *i);
void free_func(int *i);
char *find(ArrayList *list, char *ele);

typedef struct {
  void (*func)(void);
  const char *name;
} func_pointer_t;

func_pointer_t func_array[] = {
    FUNC_DEF(test_1)};

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

    for(size_t i = 0; i < 999; i++) {
        // printf("adding ele\n");
        char *elem = malloc(30 * sizeof(char));
        snprintf(elem, 30, "%lu", i);
        // gl = g_list_append(gl, elem);
        arraylist_add(l, elem);
    }

    find(l, "Tsting");

    for_each(l, print);
    // g_list_foreach(gl, print, NULL);

    printf("%s\n", (char*) arraylist_get(l, 0));
    printf("%s\n", find(l, "187"));

    arraylist_free_all(l);
    // g_list_free_full(gl, free_func);
}

char *find(ArrayList *list, char *ele) {
    char *next = arraylist_first(list);
    do{
        if(!strcmp(next, ele)) {
            return next;
        }
    } while((next = arraylist_next(list)) != NULL);

    return NULL;
}

void print(void *i) {
    printf("%s\n", (char*)i);
}
