#include "arraylist.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int no_digits(size_t nu);
int main();
void ints();
void ints_malloc();
void floats();
void floats_malloc();
void strings();
void strings_malloc();
void doPrintF(void *elem);
void doPrintZu(void *elem);
void doPrintS(void *elem);

// TODO: should these not be in test.c?
int main() {
  ints();
  ints_malloc();
  floats();
  floats_malloc();
  strings();
  strings_malloc();
}

void ints() {
  ArrayList *arr = arraylist_new();

  /* NOLINTNEXTLINE(readability-magic-numbers) */
  for (size_t i = 0; i < 100; i++) {
    arraylist_add_i(arr, (intmax_t)i, sizeof(size_t));
  }

  arraylist_foreach(arr, &doPrintZu);
  arraylist_free(arr, true);
}

void ints_malloc() {
  ArrayList *arr = arraylist_new();

  /* NOLINTNEXTLINE(readability-magic-numbers) */
  for (size_t i = 0; i < 100; i++) {
    size_t *elem = malloc(sizeof(size_t));
    *elem = i;
    arraylist_add(arr, elem);
  }

  arraylist_foreach(arr, &doPrintZu);
  arraylist_free(arr, true);
}

void floats() {
  ArrayList *arr = arraylist_new();

  /* NOLINTNEXTLINE(readability-magic-numbers) */
  for (size_t i = 0; i < 100; i++) {
    /* NOLINTNEXTLINE(readability-magic-numbers) */
    arraylist_add_f(arr, 100.0 * (double)i / 100 - 0.5, sizeof(double));
  }

  arraylist_foreach(arr, &doPrintF);
  arraylist_free(arr, true);
}

void floats_malloc() {
  ArrayList *arr = arraylist_new();

  /* NOLINTNEXTLINE(readability-magic-numbers) */
  for (size_t i = 0; i < 100; i++) {
    double *elem = malloc(sizeof(size_t));
    /* NOLINTNEXTLINE(readability-magic-numbers) */
    *elem = 100.0 * (double)i / 100 - 0.5;
    arraylist_add(arr, elem);
  }

  arraylist_foreach(arr, &doPrintF);
  arraylist_free(arr, true);
}

void strings() {
  ArrayList *arr = arraylist_new();

  /* NOLINTNEXTLINE(readability-magic-numbers) */
  for (size_t i = 0; i < 100; i++) {
    arraylist_add(arr, "Hello");
  }

  arraylist_foreach(arr, &doPrintS);
  arraylist_free(arr, false);
}

void strings_malloc() {
  ArrayList *arr = arraylist_new();

  /* NOLINTNEXTLINE(readability-magic-numbers) */
  for (size_t i = 0; i < 100; i++) {
    char *fmt = "Hello %zu!";
    size_t len = strlen(fmt) - 3 + 1 + no_digits(i);
    char *elem = malloc(len * sizeof(char));
    snprintf(elem, len, fmt, i);

    assert(len - 1 == strlen(elem));

    arraylist_add(arr, elem);
  }

  arraylist_foreach(arr, &doPrintS);
  arraylist_free(arr, true);
}

void doPrintF(void *elem) { printf("%f\n", *(double *)elem); }

void doPrintZu(void *elem) { printf("%zu\n", *(size_t *)elem); }

void doPrintS(void *elem) { printf("%s\n", (char *)elem); }

int no_digits(size_t nu) {
  if (nu == 0) {
    return 1;
  }

  int c;
  for (c = 0; nu != 0; c++) {
    /* NOLINTNEXTLINE(readability-magic-numbers) */
    nu /= 10;
  }
  return c;
}
