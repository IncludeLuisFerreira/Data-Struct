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
    node->next = node;
    node->prev = node;
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
    
    destroy_CNode(&pos);
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

void remove_CList(CList *list, int value) {
    if (is_empty(list)) {
        fprintf(stderr, "Error in 'remove_CList' ==> Trying to remove an element of an EMPTY LIST!\n");
    }
    else {
        CNode *node = list->begin;
        //case 1: value is the list begining
        if (list->begin->value == value) {
            node->prev = node->next;
            list->begin = node->next;
            list->begin->prev = list->end;
            list->size--;
            free(node);
        }
        else {
            //case 2: the value is between or at the end 
            while (node != NULL && node->value != value) {
                node = node->next;
            }
            
            if (node != NULL) {
                node->prev->next = node->next;

                if (list->end == node) {
                    list->begin->prev = node->prev;
                    list->end = node->prev;
                }
                else {
                    node->next->prev = node->prev;
                }
                free(node);
                list->size--;
            }
            else {
                fprintf(stderr, "Error in 'remove_CList' ==> Value not found!\n");
            }
        }
    }
}
size_t sizeof_CList(CList *list) {
    return list->size;
}


void insert_CList(CList *list, int value, int index) {
    if (is_empty(list) && index != 0) {
        fprintf(stderr, "Error in 'insert_CList' ==> invalid index for an EMPTY LIST!\n");
    }
    else {
        if (index == 0) {
            addFirst_CList(list, value);
        }
        else if (index == list->size) {
            addLast_CList(list, value);
        }
        else {
            CNode *node = list->begin->next;
            CNode *new = create_CNode(value);
            int j = 1;
            
            while (node != NULL && j != index) {
                node = node->next;
                j++;
            }

            new->next = node;
            new->prev = node->prev;
            node->prev->next = new;
            node->prev = new;
            list->size++;
        }
    }

}

CList *invert_CList(CList *list) {
    if (is_empty(list)) {
        fprintf(stderr, "Error in 'invert_CList' ==> Cloning an EMPTY LIST!\n");
        return list;
    }

}

CList *clone_CList(CList *list) {
    CList *clone = init_CList();
    
    if (is_empty(list)) {
        fprintf(stderr, "Cloning an EMPTY LIST, BEGIN and END set as NULL!\n");
    }
    else {
        CNode *node = list->begin;

        for (int i = 0; i < list->size; i++) {
            addLast_CList(clone, node->value);
            node = node->next;
        }
        
        printf("List cloned sucessfully!\n");
    }

    return clone;

}

void clean_CList(CList **list_ref) {
    if (is_empty(*list_ref)) {
        fprintf(stderr, "Error in 'clean_CList' ==> Trying to clean an EMPTY LIST!\n");
    }
    else {
        CList *L = *list_ref;
        CNode *node = L->begin;
        CNode *next = NULL;

        while (L->end != node) {
            next = node->next;
            free(node);
            node = next;
        }
        free(node);

        L->begin = L->end = NULL;
        L->size = 0;
    }
}

CNode *search_CList(CList *list, int value) {
    if (is_empty(list)) {
        fprintf(stderr, "Error in 'search_CList' ==> Trying to seach an EMPTY LIST!\n");
    }
    else {
        CNode *node = list->begin;

        while (node != NULL && node->value != value) {
            node = node->next;
        }

        if (node != NULL) {
            return node;
        }
        else {
            fprintf(stderr, "Value not found!\n");
            return NULL;
        }
    }
}

