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

