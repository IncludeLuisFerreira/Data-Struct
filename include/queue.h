#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct queue_val Qval;
typedef struct queue Queue;

Queue *init_queue();
Qval *create_qval(int value);
void destroy_queue(Queue **q);
bool is_null_pointer(void * pointer);
size_t sizeof_queue(Queue *q);
void enqueue(Queue *q, int value);
void dequeue(Queue *q);
Qval *peek(Queue *q); 
bool is_queue_empty(Queue *q);
void clear_queue(Queue **q_ref);
Qval *search_queue(Queue *q, int value);
void reverse_queue(Queue **q);
Queue *clone_queue(Queue *q);
void print_queue(Queue *q);

#endif