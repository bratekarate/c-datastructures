#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linkedlist.h"

#define NODE_SIZE sizeof(Node)
#define LINKED_LIST_SIZE sizeof(LinkedList)

typedef struct Node Node;

void init_list(LinkedList **list);
void init_node_p(Node **node, void *item);
void add_node(LinkedList *list, Node **node, void *item);
void print_nodes_rec_broken(Node *node);
void free_nodes(Node *node, bool items);
void free_nodes_rec_broken(Node *node);

struct LinkedList {
  Node *fst;
  Node *lst;
  size_t size;
};

struct Node {
  void *item;
  Node *prev;
  Node *next;
};

LinkedList *linkedlist_new() {
  LinkedList *list = malloc(LINKED_LIST_SIZE);
  init_list(&list);
  return list;
}

void linkedlist_add(LinkedList *list, void *item) {
  Node *node = malloc(NODE_SIZE);
  // fprintf(stderr, "Create node %p with item %s\n", node, (char*)item);
  add_node(list, &node, item);
}

void linkedlist_add_all(LinkedList *list, LinkedList *addable) {
   Node *cur = addable -> fst;  
   while (cur != NULL) {
       linkedlist_add(list, cur -> item);
       cur = cur -> next;
   }
}

// TODO: handle index out of bounds
void *linkedlist_get(LinkedList *list, size_t index){
    // TODO: if index is past middle, go backwards
    Node *cur = list -> fst;
    for(size_t i = 0; i < index; i++) {
        cur = cur -> next;
    }
    return cur -> item;
}

// TODO: handle index out of bounds (e.g. empty)
// TODO: use logic except freeing memory to subfunction
void *linkedlist_remove(LinkedList *list, size_t index){
    Node *cur = list -> fst;
    for(size_t i = 0; i < index; i++) {
        cur = cur -> next;
    }

    Node *prev = cur -> prev;
    Node *next = cur -> next;
    if(prev != NULL) {
        /*fprintf(stderr, "cur -> prev: %d\n", cur -> prev -> item);*/
        prev -> next = next;
    }

    if(next != NULL) {
        /*fprintf(stderr, "cur -> next: %d\n", cur -> next -> item);*/
        next -> prev = prev;
    }

    if (cur == list -> fst) {
        list -> fst = cur -> next;
    }

    if (cur == list -> lst) {
        list -> lst = cur -> prev;
    }

    list -> size--;

    void *item = cur -> item;
    free(cur);

    return item;
}

size_t linkedlist_size(LinkedList *list) {
    return list->size;
}

void printit(void *stuff) {
  printf("%p\n", stuff);
}

// TODO: bool property good solution?
void linkedlist_free(LinkedList *list, bool items) {
    free_nodes(list->lst, items);
    list->fst = NULL;
    list -> size = 0;
    free(list);
}

void free_nodes(Node *node, bool items) {
    while(node != NULL) {
        Node *prev = node->prev;
        /*fprintf(stderr, "Free node %p with item %d\n", node, node -> item);*/
        if (items) {
          free(node -> item);
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

void linkedlist_print(LinkedList *list, void (*printfn)(void*)) {
    fprintf(stderr, "size: %zu\n", list -> size);
    printf("[ ");
    Node *node = list -> fst;
    while (node != NULL) {
        char *rest = node -> next == NULL ? " " : ", ";
        printfn(node->item);
        printf("%s", rest);
        node = node -> next;
    }
    printf("]\n");
}

// void print_nodes_rec_broken(Node *node) {
//   if (node == NULL) {
//     return;
//   }
//   printf("%d\n", node->item);
//   print_nodes_rec_broken(node->next);
// }

void init_list(LinkedList **list) {
  LinkedList l = {.fst = NULL, .lst = NULL};
  **list = l;
}

void init_node_p(Node **node, void *item) {
  Node n = {.item = item, .next = NULL, .prev = NULL};
  memcpy(*node, &n, NODE_SIZE);
}

void add_node(LinkedList *list, Node **node, void *item) {
  init_node_p(node, item);
  // fprintf(stderr, "node -> item: %s\n", (char*)(*node) -> item);

  Node *l = list->lst;

  list->lst = *node;

  if (l == NULL) {
    list->fst = *node;
    // fprintf(stderr, "add node as first element: %s\n", (char*)list -> fst -> item);
  } else {
    l->next = *node;
    (*node)->prev = l;
    // fprintf(stderr, "add node as next element of last: %s\n", (char*)l -> next -> item);
    // fprintf(stderr, "prev element of node is: %s\n", (char*)l -> next -> prev -> item);
  }
  list->size++;
}

