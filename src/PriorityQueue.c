#include "PriorityQueue.h"
#include <stdio.h>
#include <stdlib.h>

struct cel {
    int value;
    int priority;
    Cel *next;
};

struct Pqueue {
    Cel *begin;
    Cel* end;
    size_t size;
};

int Pqueue_isEmpty(Pqueue *pq) {
    return pq->size == 0;
}


Pqueue* Pqueue_init() {
    Pqueue *newQueue = (Pqueue*) malloc(sizeof(Pqueue));

    if (!newQueue) {
        fprintf(stderr, "malloc error ==> Pqueue_init can NOT allocate memory!");
        exit(EXIT_FAILURE);
    }
    
    newQueue->begin = NULL;
    newQueue->end = NULL;
    newQueue->size = 0;
    return newQueue;
}


// precisa simplificar
void Pqueue_insert(Pqueue *pq, Cel *data) {
    if (Pqueue_isEmpty(pq)) {
        pq->begin = data;
        pq->end = data;
    }
    else {
        Cel *aux = pq->begin;
        
        if (aux->priority < data->priority) {
            pq->begin = data;
            data->next = aux;
        } else {
            while (aux->next != NULL && aux->next->priority > data->priority) {
                aux = aux->next;
            }

            if (aux->next) {
                Cel *backup = aux->next;
                aux->next = data;
                data->next = backup;
            }
            else {
                pq->end->next = data;
            }
        }
    }
    pq->size++;
}

void Pqueue_insertV2(Pqueue *pq, Cel *data) {
    if (Pqueue_isEmpty(pq)) {
        pq->begin = data;
        pq->end = data;
    }
    else {
        Cel *aux = pq->begin;
        Cel *prev = NULL;
        
        while (aux != NULL && aux->priority > data->priority) {
            prev = aux;
            aux = aux->next;
        }
        
        if (!prev) {data->next = pq->begin; pq->begin = data;}
        else {prev->next = data; data->next = aux;}
    }
    pq->size++;
}


void Pqueue_remove(Pqueue *pq) {
    if (Pqueue_isEmpty(pq)) {
        fprintf(stderr, "Segmental fault == >Pqueue_remove can NOT remove a cel from EMPTY LIST!");
    }

    Cel *removed = pq->begin;
    pq->begin = removed->next;

    free(removed);
    removed = NULL;
    pq->size--;
}


Cel* Cel_init(int value, int priority) {
    Cel *newCel = (Cel*) malloc(sizeof(Cel));

    if (!newCel) {
        fprintf(stderr, "malloc error ==> Cel_init can NOT allocate memory!");
        exit(EXIT_FAILURE);
    }

    newCel->next = NULL;
    newCel->priority = priority;
    newCel->value = value;
    return newCel;
}

void print(Pqueue *pq) {
    if (Pqueue_isEmpty(pq)) {
        printf("Empty List!\n");
        return;
    }

    for (Cel *node = pq->begin; node != NULL; node = node->next) {
        printf("Value: %d Priority: %d\n", node->value, node->priority);
    }
}

void PriorityPrint(Pqueue *pq, int priority) {
    if (Pqueue_isEmpty(pq)) {
        printf("Empty List!\n");
        return;
    }

    for (Cel *node = pq->begin; node != NULL; node = node->next) {
        if (node->priority == priority)
            printf("Value: %d Priority: %d\n", node->value, node->priority);
    }
}
