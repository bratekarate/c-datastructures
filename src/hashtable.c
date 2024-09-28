#include "hashtable.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Bucket Bucket;

typedef struct HashTable {
  size_t size;
  Bucket **buckets;
} HashTable;

typedef struct Bucket {
  size_t size;
  void *key;
  void **elements;
} Bucket;

int main() {
  HashTable *table = malloc(sizeof(HashTable));
  *table = ((HashTable){.buckets = (Bucket**)malloc(2 * sizeof(Bucket *)), .size = 2});

  table->buckets[0] = malloc(sizeof(Bucket));
  *table->buckets[0] = ((Bucket){
      .key = "key1", .elements = (void**)malloc(2 * sizeof(void *)), .size = 2});
  table->buckets[0]->elements[0] = "test1";
  table->buckets[0]->elements[1] = "test2";

  table->buckets[1] = malloc(sizeof(Bucket));
  *table->buckets[1] = ((Bucket){
      .key = "key2", .elements = (void**)malloc(1 * sizeof(void *)), .size = 1});
  table->buckets[1]->elements[0] = "test3";

  printf("%s", (char*)table->buckets[0]->key);

  for (size_t i = 0; i < 2; i++) {
    free((void*)table->buckets[i]->elements);
    table->buckets[i]->elements = NULL;
    free(table->buckets[i]);
    table->buckets[i] = NULL;
  }

  free((void*)table->buckets);
  table->buckets = NULL;
  free(table);
  table = NULL;
}
