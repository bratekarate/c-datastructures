#include "../src/arraylist.h"

#define FUNC_DEF(func) {func, #func},
#define FUNC_ARRAY_SIZE (sizeof(func_array) / sizeof(func_pointer_t))

void test_1();
void print();

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
    ArrayList *l = new_arraylist(sizeof(int));

    for(size_t i = 0; i < 100000; i++) {
        add(l, &i);
    }

    for_each(l, print);
}

void print(int *i) {
    printf("%d\n", *i);
}
