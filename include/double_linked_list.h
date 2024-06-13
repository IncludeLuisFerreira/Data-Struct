#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct _node DNode;
typedef struct double_linked DLinkedlist;

        /************************** PUBLIC FUNCTIONS ***************************/

DLinkedlist *init_DLinkedlist();
void addFirst_DLinkedlist(DLinkedlist *doubleList, int value);
void addLast_DLinkedlist(DLinkedlist *list, int value);
bool is_empty(DLinkedlist *doubleList);
bool is_null_pointer(void * p);
DNode *create_DNode(int value);
void print_DNode(DNode *node);
void print_DLinkedlist(DLinkedlist *list);
void inverted_print_DLinkedlist(DLinkedlist *doublelist);
void destroy_DLinkedlist(DLinkedlist **ref);
void remove_DLinkedlist(DLinkedlist *list, int value);
size_t size_DLinkedlist(DLinkedlist *list);
void insert_DLinkedlist(DLinkedlist *list, int value, int index);
DLinkedlist* invert_DLinkedlist(DLinkedlist *list);
DLinkedlist *clone_DLinkedlist(DLinkedlist *list);
void clean_DLinkedlist(DLinkedlist *list);
DLinkedlist *cat_DLinkedlist(DLinkedlist *fir_list, DLinkedlist *sec_list);
DNode *search_DLinkedlist(DLinkedlist *list, int value);
void sorted_insert_DLinkedlist(DLinkedlist *list, int value);

        /***********************************************************************/

#endif