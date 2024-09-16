#include "linkedlist.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE_SIZE sizeof(Node)
#define LINKED_LIST_SIZE sizeof(LinkedList)

typedef struct Node Node;

void add_node(LinkedList *list, Node **node, void *item);
void print_nodes_rec_broken(Node *node);
void free_nodes(Node *node, bool items);
void free_nodes_rec_broken(Node *node);

struct LinkedList {
  Node *fst;
  Node *lst;
  size_t size;
};

struct LinkedListIterator {
  Node *next;
  size_t i;
};

struct Node {
  void *item;
  Node *prev;
  Node *next;
};

LinkedList *linkedlist_new() {
  LinkedList *list = malloc(LINKED_LIST_SIZE);
  *list = (LinkedList){.fst = NULL, .lst = NULL};
  return list;
}

void linkedlist_add_all(LinkedList *list, LinkedList *addable) {
  Node *cur = addable->fst;
  while (cur != NULL) {
    linkedlist_add(list, cur->item);
    cur = cur->next;
  }
}

LinkedListIterator *linkedlist_iterator(LinkedList *list) {
  LinkedListIterator *it = malloc(sizeof(LinkedListIterator));
  *it = (LinkedListIterator){.i = 0, .next = list->fst};
  return it;
}

void *linkedlist_it_next(LinkedListIterator *iterator) {
  if (iterator->next == NULL) {
    return NULL;
  }

  Node *next = iterator->next;
  iterator->next = iterator->next->next;
  iterator->i++;
  return next->item;
}

size_t linkedlist_it_i(LinkedListIterator *iterator) { return iterator->i; }

void *linkedlist_get(LinkedList *list, size_t index) {
  if (index >= list->size) {
    errno = 1;
    return NULL;
  }

  Node *cur;
  if (index < list->size/2) {
    cur = list->fst;
    for (size_t i = 0; i < index; i++) {
      cur = cur->next;
    }
  } else {
    cur = list->lst;
    for (size_t i = list->size - 1; i > index; i--) {
      cur = cur->prev;
    }
  }
  return cur->item;
}

void *linkedlist_get_last(LinkedList *list) {
  if (list->lst == NULL) {
    errno = 1;
    return NULL;
  }

  return list->lst->item;
}

void *linkedlist_remove(LinkedList *list, size_t index) {
  if (index >= list->size) {
    errno = 1;
    return NULL;
  }

  Node *cur = list->fst;
  for (size_t i = 0; i < index; i++) {
    if (i < index) {
      cur = cur->next;
    }
  }

  Node *prev = cur->prev;
  Node *next = cur->next;
  if (prev != NULL) {
    prev->next = next;
  }

  if (next != NULL) {
    next->prev = prev;
  }

  if (cur == list->fst) {
    list->fst = cur->next;
  }

  if (cur == list->lst) {
    list->lst = cur->prev;
  }

  list->size--;

  void *item = cur->item;
  free(cur);

  return item;
}

size_t linkedlist_size(LinkedList *list) { return list->size; }

void linkedlist_free(LinkedList *list, bool items) {
  free_nodes(list->lst, items);
  list->fst = NULL;
  list->size = 0;
  free(list);
}

void free_nodes(Node *node, bool items) {
  while (node != NULL) {
    Node *prev = node->prev;
    if (items) {
      free(node->item);
    }
    free(node);
    node = prev;
  }
}

// void free_nodes_rec_broken(Node *node) {
//   if (node == NULL) {
//     return;
//   }
//   free_nodes_rec_broken(node->next);
//   /*ffprintf(stderr, "stderr, Free node %p\n", node);*/
//   free(node);
//   node = NULL;
// }

void linkedlist_print(LinkedList *list, void (*printfn)(void *)) {
  printf("[ ");
  Node *node = list->fst;
  while (node != NULL) {
    char *rest = node->next == NULL ? " " : ", ";
    printfn(node->item);
    printf("%s", rest);
    node = node->next;
  }
  printf("]\n");
}

void linkedlist_insert(LinkedList *list, size_t pos, void *item) {
  if (pos > list->size) {
    errno = 1;
    return;
  }

  if (pos == list->size) {
    Node *node = malloc(NODE_SIZE);
    *node = (Node){.item = item, .next = NULL, .prev = NULL};

    Node *l = list->lst;
    list->lst = node;

    if (l == NULL) {
      list->fst = node;
    } else {
      l->next = node;
      node->prev = l;
    }
    list->size++;
    return;
  }

  Node *node;
  if (pos < list->size/2) {
    node = list->fst;
    for (size_t i = 0; i < pos && node != NULL; i++) {
      node = node->next;
    }
  } else {
    node = list->lst;
    for (size_t i = list->size - 1; i > pos && node != NULL; i--) {
      node = node->prev;
    }
  }

  Node *new = malloc(NODE_SIZE);
  *new = (Node){.item = item, .next = node, .prev = node->prev};
  if (node->prev) {
    node->prev->next = new;
  } else {
    list->fst = new;
  }
  node->prev = new;
  list->size++;
}

void linkedlist_add(LinkedList *list, void *item) {
  linkedlist_insert(list, 0, item);
}
