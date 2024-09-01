#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

typedef struct cel Cel;
typedef struct Pqueue Pqueue;

    /************************* Functions prototypes *************************/

Pqueue* Pqueue_init();
void Pqueue_insert(Pqueue *pq, Cel *data);
void Pqueue_remove(Pqueue *pq);
int Pqueue_isEmpty(Pqueue *pq);
void Pqueue_insertV2(Pqueue *pq, Cel *data);

Cel* Cel_init(int value, int priority);

void print(Pqueue *pq);
void PriorityPrint(Pqueue *pq, int priority);

#endif