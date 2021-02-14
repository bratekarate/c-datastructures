#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE_SIZE sizeof(Node)
#define LINKED_LIST_SIZE sizeof(LinkedList)

typedef struct Node Node;
typedef struct LinkedList LinkedList;

// High level functions
LinkedList *linkedlist_new();
void linkedlist_add(LinkedList *list, void *item);
void linkedlist_add_all(LinkedList *list, LinkedList *addable);
void *linkedlist_get(LinkedList *list, size_t index);
void *linkedlist_remove(LinkedList *list, size_t index);
size_t linkedlist_size(LinkedList *list);
void linkedlist_print(LinkedList *list, void printfn(void*));
void linkedlist_free(LinkedList *list);

// Low level functions
void init_list(LinkedList **list);
void init_node_p(Node **node, void *item);
void add_node(LinkedList *list, Node **node, void *item);
void print_nodes_rec_broken(Node *node);
void print_nodes(Node *node, void *printfn(void*));
void free_nodes(Node *node);
void free_nodes_rec_broken(Node *node);

typedef struct Node {
  void *item;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct LinkedList {
  Node *fst;
  Node *lst;
  size_t size;
} LinkedList;


LinkedList *linkedlist_new() {
  LinkedList *list = malloc(LINKED_LIST_SIZE);
  init_list(&list);
  return list;
}

void linkedlist_add(LinkedList *list, void *item) {
  Node *node = malloc(NODE_SIZE);
  /*printf("Create node %p\n", node);*/
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
        /*printf("cur -> prev: %d\n", cur -> prev -> item);*/
        prev -> next = next;
    }

    if(next != NULL) {
        /*printf("cur -> next: %d\n", cur -> next -> item);*/
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

// TODO: how to set null
void linkedlist_free(LinkedList *list) {
    free_nodes(list->lst);
    free(list);
}

// TODO: how to set null
void free_nodes(Node *node) {
    while(node != NULL) {
        Node *prev = node->prev;
        /*printf("Free node %p with item %d\n", node, node -> item);*/
        free(node);
        node = prev;
    }
}

void free_nodes_rec_broken(Node *node) {
  if (node == NULL) {
    return;
  }
  free_nodes_rec_broken(node->next);
  /*printf("Free node %p\n", node);*/
  free(node);
  node = NULL;
}

// TODO: make tostring
void linkedlist_print(LinkedList *list, void printfn(void*)) {
    print_nodes(list->fst, printfn);
}

void print_nodes(Node *node, void *printfn(void*)) {
    printf("[ ");
    while (node != NULL) {
        char *rest = node -> next == NULL ? " " : ", ";
        printfn(node->item);
        printf("%s", rest);
        node = node -> next;
    }
    printf("]\n");
}

void print_nodes_rec_broken(Node *node) {
  if (node == NULL) {
    return;
  }
  printf("%d\n", node->item);
  print_nodes_rec_broken(node->next);
}

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

  Node *l = list->lst;

  list->lst = *node;

  if (l == NULL) {
    list->fst = *node;
  } else {
    l->next = *node;
    (*node)->prev = l;
  }
  list->size++;
}

