#include "double_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

        /************************** PRIVATE STRUCT ***************************/

struct _node {
    int value;
    struct _node *next, *prev;
};

struct double_linked {
    DNode *begin;
    DNode *end;
    size_t size;
};


        /********************************** FUNCTION DECLARATION ***********************************/

DLinkedlist *init_DLinkedlist() {
    DLinkedlist *list = (DLinkedlist*)malloc(sizeof(DLinkedlist));
    
    if (list == NULL) {
        fprintf(stderr, "Error in 'Dlinkedlist_init' ==> failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
    return list;
}

DNode *create_DNode(int value) {
    DNode *node = (DNode*)malloc(sizeof(DNode));
    
    if (node == NULL) {
        fprintf(stderr, "Error in 'DNode_create' ==> failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    node->next = NULL;
    node->prev = NULL;
    node->value = value;

    return node;
}

bool is_empty(DLinkedlist *doubleList) {
    return doubleList->size == 0;
}

void addFirst_DLinkedlist(DLinkedlist *doubleList, int value) {
   DNode *node = create_DNode(value);
   node->next = doubleList->begin;
   
   if (is_empty(doubleList)) {
        doubleList->end = node;
   }
   else {
        doubleList->begin->prev = node;
   }

   doubleList->begin = node;
   doubleList->size++;
}

void addLast_DLinkedlist(DLinkedlist *list, int value) {
    DNode *node = create_DNode(value);
    
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

void print_DNode(DNode *node) {
    printf("%d -> ", node->value);
}

void print_DLinkedlist(DLinkedlist *list) {
    if (is_empty(list)) {
        fprintf(stderr, "Error in 'print_DLinkedlist' ==> Trying to print an EMPTY LIST\n");
    }
    else {
        printf("Begin -> ");
        for (DNode *node = list->begin; node != NULL; node = node->next) {
            print_DNode(node);
        }
        printf("NULL\n");
    }
}

void inverted_print_DLinkedlist(DLinkedlist *doublelist) {
    if (is_empty(doublelist)) {
        fprintf(stderr, "Error in 'inverted_print_DLinkedlist' ==> Trying to print an EMPTY LIST\n");
    }
    else {
        DNode *node;
        printf("End -> ");
        for (node = doublelist->end; node != NULL; node = node->prev) {
            print_DNode(node);
        }
        printf("NULL\n");
    }
}

void destroy_DLinkedlist(DLinkedlist **ref) {
    DLinkedlist *L = *ref;
    
    DNode *p = L->begin;
    DNode *aux = NULL;
    
    while (p != NULL) {
        aux = p;
        p = p->next;
        free(aux);
    }
    free(L);
    
    *ref = NULL;
}

void remove_DLinkedlist(DLinkedlist *list, int value) {
    if (!is_empty(list)) {
        DNode *node = list->begin;
        
        //caso 1: o elemento está no começo
        if (list->begin->value == value) {
            list->begin = node->next;

            if (list->end == node) {
                list->end = NULL;
            }
            else {
                list->begin->prev = NULL;
            }

            free(node);
            list->size--;
        }
        else  {
            //Caso 2 e 3: o elemento está no meio ou no final da lista
           node = node->next;

            while (node != NULL) {
                if (node->value == value) {
                    node->prev->next = node->next;
                    //elemento no final da lista
                    if (list->end == node) {
                        list->end = node->prev;
                    }
                    //elemento no meio da lista
                    else {
                        node->next->prev = node->prev; 
                    }

                    free(node);
                    list->size--;
                    node = NULL;
                }
                else {
                    node = node->next;
                }
            }
        }
    }
    else {
        fprintf(stderr, "Error in 'remove_DLinkedlist' ==> trying to remove an EMPTY list");
    }
}

size_t size_DLinkedlist(DLinkedlist *list) {
    return list->size;
}

bool is_null_pointer(void * p) {
    return p == NULL;
}

void insert_DLinkedlist(DLinkedlist *list, int value, int index) {
    if (is_empty(list) && index != 0) {
        fprintf(stderr, "Error in 'insert_DLinkedlis' ==> invalid index.\n** EMPTY list\n"); 
    }
    else if (index < 0 || index > list->size) {
        fprintf(stderr, "Error in 'insert_DLinkedlist' ==> invalid index.\n** Index out of bounds [0, %d[\n", list->size);
    }
    else {
        //case 1: The user wants to add a new value on the begining of the list
        if (index == 0) {
            addFirst_DLinkedlist(list, value);
        }
        //case 2: The user wants do add a new value on the end of the list
        else if (index == list->size) {
            addLast_DLinkedlist(list, value);
        }
        //case 3: User wants to add the value on the middle of the list
        else {
            DNode *node = create_DNode(value);
            DNode *pos = list->begin->next;
            int j = 1;

            while (pos != NULL && j != index) {
                pos = pos->next;
                j++;
            }
            
            pos->prev->next = node;
            node->next = pos;
            
            list->size++;
        }
    }
}

DLinkedlist* invert_DLinkedlist(DLinkedlist *list) {
    if (is_empty(list)) {
        fprintf(stderr, "Error in 'invert_DLinkedlist' ==>Trying to invert an EMPTY LIST!\n");
    }
    else {
        DLinkedlist *copy = init_DLinkedlist();
        for (DNode *node = list->begin; node != NULL; node = node->next) {
            addFirst_DLinkedlist(copy, node->value);
        }
        destroy_DLinkedlist(&list);
        return copy;
    }
}

DLinkedlist *clone_DLinkedlist(DLinkedlist *list) {
    DLinkedlist *copy = init_DLinkedlist();

    // Cloned an Empty list 
    if (is_empty(list)) {
        printf("EMPTY LIST ==> begin member set as NULL!\n");
    }
    else {
        for (DNode *node = list->begin; node != NULL; node = node->next) {
            addLast_DLinkedlist(copy, node->value);
        }
    }

    copy->size = list->size;
    return copy; 
}

void clean_DLinkedlist(DLinkedlist *list) {
    if (!is_empty(list)) {
        DNode *current = list->begin;
        DNode *next = NULL;

        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }

        list->size = 0;
        list->begin = NULL;
        list->end = NULL;
    }
}

DLinkedlist *cat_DLinkedlist(DLinkedlist *fir_list, DLinkedlist *sec_list) {
    if (is_empty(fir_list) || is_empty(sec_list)) {
        fprintf(stderr, "Error in 'cat_DLinkedlist' ==> Trying to concatenate two EMPTY LIST!\n");
        exit(EXIT_FAILURE);
    }
    else {
        DLinkedlist *cat = init_DLinkedlist();
        
        for (DNode *node = fir_list->begin; node != NULL; node = node->next) {
            addLast_DLinkedlist(cat, node->value);
        }
        for (DNode *node = sec_list->begin; node != NULL; node = node->next) {
            addLast_DLinkedlist(cat, node->value);
        }
        return cat;
    }
}

DNode *search_DLinkedlist(DLinkedlist *list, int value) {
    if (is_empty(list)) {
        fprintf(stderr, "Error in 'search_DLinkedlist' ==> Trying to traverse an EMPTY LIST!\n");
    }
    else {
        DNode *node = list->begin;

        while (node != NULL && node->value != value) {
            node = node->next;
        }
        
        if (node != NULL) {
            return node;
        }
        else {
            fprintf(stderr, "Error in 'search_DLinkedlist' ==> Value is not on the list!\n");
        }
    }
    return NULL;
}

void sorted_insert_DLinkedlist(DLinkedlist *list, int value) {
    if (!list) {
        fprintf(stderr, "\033[31mError in 'sorted_insert_DLinkedlist' ==> Trying to insert an EMPTY LIST!\033[0m\n");
        exit(EXIT_FAILURE);
    }





}
        

