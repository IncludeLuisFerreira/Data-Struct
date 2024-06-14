#include "../include/circular_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

        /****************************** PRIVATE STRUCTS *******************************/
    
struct _node {
    int value;
    struct _node *next, *prev;
};

struct list {
    CNode *begin;
    CNode *end;
    size_t size;
};

        /*******************************************************************************/

        /************************** FUNCTION DECLARATION*********************************/

CList* init_CList() {
    CList *list = (CList*)malloc(sizeof(CList));
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;

    return list;
}

CNode* create_CNode(int value) {
    CNode *node = (CNode*)malloc(sizeof(CNode));
    node->next = NULL;
    node->prev = NULL;
    node->value = value;

    return node;
}

void destroy_CNode(CNode **node_ref) {
    free(*node_ref);
    *node_ref = NULL;
}

void destroy_CList(CList **list_ref) {
    CList *L = *list_ref;

    CNode *next = NULL;
    CNode *pos = L->begin;

    while (pos != L->end) {
        next = pos->next;
        destroy_CNode(&pos);
        pos = next;
    }
    
    free(L);
    *list_ref = NULL;
}

bool is_empty(CList *list) {
    return list->size == 0;
}

void addFirst_CList(CList *list, int value) {
    CNode *node = create_CNode(value);
    node->next = list->begin;

    if (is_empty(list)) {
        list->end = node;

    }
    else {
        list->begin->prev = node;
       
    }

    list->begin = node;
    list->size++;
}

void addLast_CList(CList *list, int value) {
    CNode *node = create_CNode(value);

    if (is_empty(list)) {
        list->begin = node;
    }
    else {
        list->end->next = node;
        node->prev = list->end;
    }

    list->end = node;
    list->size++;
}

void print_CList(CList *list) {
    if (is_empty(list)) {
        fprintf(stderr, "Error in 'print_CList' ==> Trying to traverse an EMPTY LIST!\n");
    }
    else {
        CNode *node = list->begin;
        printf("L -> ");
        for (int i = 0; i < list->size; i++, node = node->next) {
            printf("%d -> ", node->value);
            
        }
        printf("NULL\n");
    }
}

void inverted_print_CList(CList *list) {
    if (is_empty(list)) {
        fprintf(stderr, "Error in 'inverted_print_CList' ==> Trying to traverse an EMPTY LIST!\n");
    }
    else {
        CNode *node = list->end;
        printf("L -> ");
        for (int i = 0; i < list->size; i++, node = node->prev) {
            printf("%d -> ", node->value);
        }
        printf("NULL\n");
    }
}
