#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>

                    /**************** PUBLIC STRUCTS AND FUNCTIONS *******************/
                    
typedef struct _node CNode;
typedef struct list CList;

CList *init_CList();
CNode *create_CNode(int value);
void destroy_CNode(CNode **node_ref);
void destroy_CList(CList **list_ref);
bool is_empty(CList *list);
void addFirst_CList(CList *list, int value);
void addLast_CList(CList *list, int value);
void print_CList(CList *list);
void inverted_print_CList(CList *list);
void remove_CList(CList *list, int value);
size_t sizeof_CList(CList *list);
void insert_CList(CList *list, int value, int index);
CList *invert_CList(CList *list);
CList *clone_CList(CList *list);
void clean_CList(CList **list_ref);
CNode *search_CList(CList *list, int value);

                    /*****************************************************************/

#endif
