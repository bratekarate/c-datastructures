#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct HashTable HashTable;

HashTable *hashtable_new();
void hashtable_put(HashTable *hashtable, void *key, void *value);
void hashtable_put_all(HashTable *hashtable_dst, HashTable *hashtable_src);
void *hashtable_get(HashTable *hashtable, void *key);
void *hashtable_remove(HashTable *hashtable, void *key);
void *hashtable_print(HashTable *hashtable, void *key);
void *hashtable_free(HashTable *hashtable, void *key);
// void **hashtable_keys(HashTable *hashtable, void *key);
// void **hashtable_values(HashTable *hashtable, void *key);

#endif
