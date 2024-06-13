#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct _node Node;
typedef struct _linked_list LinkedList;

   /************ FUNCTION PROTOTYPES ***********/

LinkedList *Linked_list_Create();
Node *Node_create(int value);

bool Linked_list_is_empty(const LinkedList *list);
void Linked_list_addFirst(LinkedList *list, int value);
void print_Linked_list(LinkedList *list);
void Linked_list_addLast_slow(LinkedList *list, int value);
void Linked_list_addLast_quick(LinkedList *list, int value);
void Linked_list_remove(LinkedList *list, int value);
void Linked_list_remove_v2(LinkedList *list, int value);
void Linked_list_destroy(LinkedList **list_ref);
size_t LinkedList_size(LinkedList *list);
int LinkedList_first_value(LinkedList *list);
int LinkedList_last_value(LinkedList *list);
int LinkedList_get_value(LinkedList *list, int index);
void Linked_list_insert(LinkedList *list, int index, int value);
LinkedList *Linked_list_invert(LinkedList *list);
void Linked_list_invert_v2(LinkedList **list_ref);
LinkedList * Linked_list_copy(LinkedList *list);
void Linked_list_delete_all_Value(LinkedList **list_ref);
LinkedList *Linked_list_cat(const LinkedList *fir_list, const LinkedList *sec_list);
void sort_list(LinkedList *list);
Node *Linked_list_search(LinkedList *list, int value);
void print_Node(Node *node);
void Linked_list_sorted_insert(LinkedList *list, int value);
   /****************************************/
#endif