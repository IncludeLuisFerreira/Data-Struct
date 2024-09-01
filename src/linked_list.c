#include "../include/linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct _node {
    int value;
    struct _node *next;
};

struct _linked_list {
    Node *begin;
    Node *end;      //Melhora o processamento do código
    int size;
};

// Função auxiliar para dividir a lista em duas metades
Node* get_middle(Node* head) {
    if (head == NULL) return head;

    Node* slow = head;
    Node* fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Função auxiliar para mesclar duas listas ordenadas
Node* sorted_merge(Node* a, Node* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    Node* result = NULL;
    if (a->value <= b->value) {
        result = a;
        result->next = sorted_merge(a->next, b);
    } else {
        result = b;
        result->next = sorted_merge(a, b->next);
    }
    return result;
}

// Função recursiva do merge sort
Node* merge_sort(Node* head) {
    if (head == NULL || head->next == NULL) return head;

    Node* middle = get_middle(head);
    Node* next_of_middle = middle->next;
    middle->next = NULL;

    Node* left = merge_sort(head);
    Node* right = merge_sort(next_of_middle);

    return sorted_merge(left, right);
}

// Função para ordenar a lista usando merge sort
void sort_list(LinkedList *list) {
    list->begin = merge_sort(list->begin);

    // Atualizando o ponteiro end
    if (list->begin == NULL) {
        list->end = NULL;
    } else {
        Node* current = list->begin;
        while (current->next != NULL) {
            current = current->next;
        }
        list->end = current;
    }
}

LinkedList *Linked_list_Create() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
        if (list == NULL) {
            fprintf(stderr, "Error: faild to allocate memory!\n");
            exit(EXIT_FAILURE);
        }
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;


    return list;
}

bool Linked_list_is_empty(const LinkedList *list) {
    return list->size == 0;
}


Node *Node_create(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    
        if (new_node == NULL) {
            fprintf(stderr, "Error: faild to create a new node!\n");
            exit(EXIT_FAILURE);
        }
    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}

void Linked_list_addFirst(LinkedList *list, int value) {
    Node *new_node = Node_create(value);
    new_node->next = list->begin;

    if (Linked_list_is_empty(list)) {
        list->end = new_node;
    }
    
    list->begin = new_node;
    list->size++;
}

void print_Linked_list(LinkedList *list) {
    if (Linked_list_is_empty(list)) {
        printf("\nEmpty list!\n");
        return ;
    }

    int i = 0;
    printf("\nTamanho: %ld\n\n", list->size);
    printf("List -> ");
    for (Node *aux = list->begin; aux != NULL; aux = aux->next) {
       printf("%d -> ", aux->value);
    }
    printf("NULL\nEnd -> %d", list->end->value);
}

void Linked_list_addLast_slow(LinkedList *list, int value) {
    Node *new_node = Node_create(value);
    
    if (Linked_list_is_empty(list)) { 
        list->begin = new_node;
    }
    else {
        Node *aux =list->begin;
        
        while(aux->next != NULL) 
            aux = aux->next;
        aux->next = new_node;
    }
    list->size++;
}
//Better performance
void Linked_list_addLast_quick(LinkedList *list, int value) {
    Node *new_node = Node_create(value);
    
    if (Linked_list_is_empty(list)) {
        list->begin = new_node;
    }
    else {
        list->end->next = new_node;
    }

    list->end = new_node;
    list->size++;
}

void Linked_list_remove(LinkedList *list, int value) {
    if (!Linked_list_is_empty(list)) {
        //caso 1: o elemento está no começo
        if (list->begin->value == value) {
            Node *pos = list->begin;
            
            if (list->begin == list->end) {
                list->end = NULL;
            }
            list->begin = list->begin->next;
            free(pos);
            list->size--;
        }
        //caso 2- o elemento está no meio da lista
        else {
            Node *prev = list->begin;
            Node *pos = list->begin->next;
            
            while(pos != NULL && pos->value != value) {
                prev = prev->next;
                pos = pos->next;
            }
            
            //Nó encontrado
            if (pos != NULL) {
                prev->next = pos->next;

                if (pos->next == NULL) {
                    list->end = prev;
                }
                free(pos);
                list->size--;
            }
        }
    }
}

void Linked_list_remove_v2(LinkedList *list, int value) {
    if (!Linked_list_is_empty(list)) {
        Node *prev = NULL;
        Node *pos = list->begin;
        
        while (pos != NULL && pos->value != value) {
            prev = pos;
            pos = pos->next;
        }
        
        if (pos != NULL) {
            if (list->end == pos) {
                list->end = prev;
            }
            if (list->begin == pos) {
                list->begin = list->begin->next;
            }
            else {
                prev->next = pos->next;
            }

            free(pos);
            list->size--;
        }
    }
}

void Linked_list_destroy(LinkedList **list_ref) {
    LinkedList *L = *list_ref;
    
    Node *p = L->begin;
    Node *aux = NULL;
    
    while (p != NULL) {
        aux = p;
        p = p->next;
        free(aux);
    }
    free(L);

    *list_ref = NULL;
}

// I think this func has a worse performance than I make the camp size in the struct
size_t LinkedList_size(LinkedList *list) {
    return list->size;
}

int LinkedList_first_value(LinkedList *list) {
    if (Linked_list_is_empty(list)) {
        printf("\nEmpty list!\n");
        return INT_MIN;
    }
    else {
        return list->begin->value;
    }
}

int LinkedList_last_value(LinkedList *list) {
    if (Linked_list_is_empty(list)) {
        printf("\nEmpty list\n");
        return INT_MIN;
    }
    else {
        return list->end->value;
    }
}

int LinkedList_get_value(LinkedList *list, int index) {
    if (Linked_list_is_empty(list)) {
        printf("\nEmpty list\n");
        return INT_MIN;
    }
    else if (index < 0 || index >= list->size){
        fprintf(stderr, "\nError: invalid index!\n");
        fprintf(stderr, "try index : [0, %d[\n", list->size);
        return INT_MIN;
    }
    else {
        Node *pos = list->begin;
        int i = 0;
        
        while (i != index) {
            pos = pos->next;
            i++;
        }
        
        return pos->value;
    }
}

void Linked_list_insert(LinkedList *list,const int index, int value) {
    if (Linked_list_is_empty(list)) {

        if (index != 0){
            fprintf(stderr, "Error in 'Linked_list_insert' : invalid index!\n");
            fprintf(stderr, "Index invalid for a empty list\ntry index 0");
        }
        else {
            Linked_list_addFirst(list, value);
        }
    }
    else if (index < 0 || index > list->size ) {
        fprintf(stderr, "Error in 'Linked_list_insert' : invalid index!\n");
        fprintf(stderr, "Index out of bounds [0, %d[\n", list->size);
    }
    else {
        if (index == 0) {
            Linked_list_addFirst(list, value);
        }
        else if (index == list->size) {
            Linked_list_addLast_quick(list, value);
        }
        else {
            Node *prev = NULL;
            Node *pos = list->begin;
            Node *new_node = Node_create(value);
            int i = 0;

            while (i != index) {
                prev = pos;
                pos = pos->next;
                i++;
            }
            
            prev->next = new_node;
            new_node->next = pos;
            list->size++;
        }
    }
}

//Acho que é ineficiente pq cria outra lista e eu tenho que desalocar a primeira
LinkedList *Linked_list_invert(LinkedList *list){
    if (Linked_list_is_empty(list)) {
        fprintf(stderr, "Error in 'Linked_list_invert': empty list");
        return NULL;
    }
    else {
        Node *p = list->begin;
        LinkedList *inverted = Linked_list_Create();

        for (; p != NULL; p =p->next) {
            Linked_list_addFirst(inverted, p->value);
        }

        Linked_list_destroy(&list);
        return inverted;
    }
}

void Linked_list_invert_v2(LinkedList **list) {
    if (Linked_list_is_empty(*list)) {
        fprintf(stderr, "Error in 'Linked_list_invert': empty list");
    }
    else {
        Node *prev = NULL;
        Node *current = (*list)->begin;
        Node *next = NULL;
        Node *backup = (*list)->begin;

        while (current != NULL) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        (*list)->begin = prev;
        (*list)->end = backup;
    }
}

LinkedList * Linked_list_copy(const LinkedList *list) {
    LinkedList *new_list = Linked_list_Create();

    if (Linked_list_is_empty(list)) {
        printf("Empty list ==> begin is set as NULL!\n");
    }
    else {
        
        for (Node *p = list->begin; p != NULL; p = p->next) {
            Linked_list_addLast_quick(new_list, p->value);
        }
    }
    return new_list;
}

void Linked_list_delete_all_Value(LinkedList **list_ref) {
    if (Linked_list_is_empty(*list_ref)) {
        fprintf(stderr, "Error in 'Linked_list_delete_all_value': empty list!\n");
    }
    else {
        Node *next = NULL;
        Node *current = (*list_ref)->begin;
        
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
        (*list_ref)->size = 0;
    }
}

LinkedList *Linked_list_cat(const LinkedList *fir_list, const LinkedList *sec_list) {
    if (Linked_list_is_empty(fir_list) || Linked_list_is_empty(sec_list)) {
        fprintf(stderr, "Error in 'Linked_list_cat'==> Empty list\n");
        exit(EXIT_FAILURE);
    }
    else {
        LinkedList *cat = Linked_list_Create();
        
        for (Node *p = fir_list->begin; p != NULL; p = p->next) {
            Linked_list_addLast_quick(cat, p->value);
        }
        
        for (Node *p = sec_list->begin; p != NULL; p = p->next) {
            Linked_list_addLast_quick(cat, p->value);
        }

        return cat;
    }
}

// I guess this isn't correct
void Linked_list_sort(LinkedList **list_ref) {
    if (Linked_list_is_empty(*list_ref)) {
        fprintf(stderr, "Error in 'Linked_list_sort' ==> trying to sort an EMPTY list\n");
    }
    else {
        LinkedList *L = *list_ref;
        Node *current = L->begin;
        Node *next = NULL;
        Node *backup = NULL;

        while(current != NULL) {
            next = current->next;
            if (next->value > current->value) {
                Node *temp = next;
                *next = *current;
                *current = *temp;
            }
            current = current->next;
        }
    }
}

Node *Linked_list_search(LinkedList *list, int value) {
    if (Linked_list_is_empty(list)) {
        fprintf(stderr, "Error in 'Linked_list_search' ==> no value allocated\n");
        return NULL;
    }
    else {
        Node *pos = list->begin;

        while (pos != NULL  && pos->value != value) {
            pos = pos->next;
        }
        
        if (pos != NULL) {
            return pos;
        }
        else {
            fprintf(stderr, "\n**Error in 'Linked_list_search' ==> value not found\n");
            return NULL;
        }
    }
}

void print_Node(Node *node) {
    if (node != NULL) {
        printf("Valor do node: %d\n", node->value);
    }
    else {
        printf("Valor do node: NULL");
    }
}

void Linked_list_sorted_insert(LinkedList *list, int value) {
    Node* new_node = Node_create(value);

    if (list->begin == NULL || list->begin->value >= value) {
        new_node->next = list->begin;
        list->begin = new_node;
    } else {
        Node* current = list->begin;
        while (current->next != NULL && current->next->value < value) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }

    if (new_node->next == NULL) {
        list->end = new_node;
    }
    list->size++;
}

