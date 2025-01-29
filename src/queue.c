#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/**************************************************************** PRIVATE STRUCT ****************************************************************/

struct queue_val {
    int value;
    struct queue_val *next;
};

struct queue {
    Qval *front;
    Qval *tail;
    size_t size;
};

/******************************************************************************************************************************************/

/********************************************************** FUNCTIONS DECLARATIONS ********************************************************/

Queue *init_queue() {
    Queue *q = (Queue*) malloc(sizeof(Queue));
    
    if (is_null_pointer(q)) {
        fprintf(stderr, "malloc error!\n");
    }
    q->front = NULL;
    q->size = 0;

    return q;
}

Qval *create_qval(int value) {
    Qval *val = (Qval*) malloc(sizeof(Qval));

    if (is_null_pointer(val)) {
        fprintf(stderr, "malloc error!\n");
    }
    val->next = NULL;
    val->value = value;
    
    return val;
}

size_t sizeof_queue(Queue *q) {
    return q->size;
}

void destroy_queue(Queue **q) {
    if (!is_queue_empty(*q)) {

        Qval *node = (*q)->front;
        Qval *next = NULL;

        while (!is_null_pointer(node)) {
            next = node->next;
            free(node);
            node = next;
        }
    }

    free(*q); 
    *q = NULL;
}


void enqueue(Queue *q, int value) {
    Qval *node = create_qval(value);
    
    if (is_queue_empty(q)) {
        q->front = node;
        q->tail = node;
    }
    else {
        q->tail->next = node;
        q->tail = node;
    }
    q->size++;

}

void dequeue(Queue *q) {
    if (is_queue_empty(q)) {
        fprintf(stderr, "Error in 'dequeue' ==> Trying to dequeue an EMPTY LIST!\n");
    }
    Qval *node = q->front;
    q->front = q->front->next;
    q->size--;

    free(node);
}

Qval* peek(Queue *q) {
    return q->front;
}

bool is_queue_empty(Queue *q) {
    return q->size == 0;
}

void clear_queue(Queue **q) {
    Queue *Q = *q;
    
    Qval *node = Q->front;
    Qval *next = NULL;
    
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }

    Q->tail = NULL;
    Q->front = NULL;
    Q->size = 0;
}

bool is_null_pointer(void * pointer) {
    return pointer == NULL;
}

Qval *search_queue(Queue *q, int value) {
    if (is_queue_empty(q)) {
        fprintf(stderr, "Searching an EMPTY LIST!\n");
    }
    else {
        Qval *node = q->front;

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

void reverse_queue(Queue **q) {
    Qval *node = (*q)->front;
    size_t tam = (*q)->size;
    int vec[tam];
    
    for (int i = 0; i < tam; i++, node = node->next)
        vec[i] = node->value;

    Queue *rev = init_queue();

    for (int i = tam-1; i >= 0; i--)
        enqueue(rev, vec[i]);

    destroy_queue(q);
    *q = rev;
}

void print_queue(Queue *q) {
    if (is_null_pointer(q)) { return; }

    if (is_queue_empty(q)) {
        fprintf(stderr, "EMPTY QUEUE!\n");
    }
    else {
        for (Qval *node = q->front; node != NULL; node = node->next) {
            printf("%d -> ", node->value);
        }
        printf("NULL\n");
    }
}

Queue *clone_queue(Queue *q) {
    Queue *clone = init_queue();

    if (is_queue_empty(q)) {
        fprintf(stderr, "Cloning an EMPTY LIST! Front and Tail set as NULL\n");
    }
    else {
        Qval *node = q->front;
       
        for (; node != NULL; node = node->next)
            enqueue(clone, node->value);
        
    }
    return clone;
}


int sum_Queue(Queue *q) {
    if (is_queue_empty(q)) {
        fprintf(stderr, "Trying to sum an EMPTY LIST! Returning 0\n");
    }
    else {
        Qval *node = q->front;
        int sum = 0;
        
        for (; node != NULL; node = node->next) 
            sum += node->value;

        return sum;
    }
}

void dequeue_NTimes(Queue *q, int pos) {
    if (is_queue_empty(q)) {
        fprintf(stderr, "Error: Trying to dequeue an EMPTY LIST!\n");
    }
    else {
        if (pos < 0 || pos > q->size) {return ;}

        for (int it = 0; it < pos; it++) {
            dequeue(q);
        }
    }
}


/******************************************************************************************************************************************/