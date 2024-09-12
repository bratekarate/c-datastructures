#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct HashTable HashTable;
typedef struct Bucket Bucket;

HashTable *hashtable_new();
void hashtable_put(HashTable *hashtable, void *key, void *value);
void hashtable_put_all(HashTable *hashtable_dst, HashTable *hashtable_src);
void *hashtable_get(HashTable *hashtable, void *key);
void *hashtable_remove(HashTable *hashtable, void *key);
void hashtable_print(HashTable *hashtable, void *key);
void hashtable_free(HashTable *hashtable, void *key);

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
  *table = ((HashTable){.buckets = malloc(2 * sizeof(Bucket *)), .size = 2});

  table->buckets[0] = malloc(sizeof(Bucket));
  *table->buckets[0] = ((Bucket){
      .key = "key1", .elements = malloc(2 * sizeof(void *)), .size = 2});
  table->buckets[0]->elements[0] = "test1";
  table->buckets[0]->elements[1] = "test2";

  table->buckets[1] = malloc(sizeof(Bucket));
  *table->buckets[1] = ((Bucket){
      .key = "key2", .elements = malloc(1 * sizeof(void *)), .size = 1});
  table->buckets[1]->elements[0] = "test3";

  printf("%s", (char*)table->buckets[0]->key);
}
