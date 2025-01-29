#include "PriorityQueue.h"
#include <stdio.h>

int main() {
    Pqueue *teste = Pqueue_init();
    print(teste);

    Pqueue_insertV2(teste, Cel_init(10, 1));
    Pqueue_insertV2(teste, Cel_init(132, 5));
    Pqueue_insertV2(teste, Cel_init(32, 2));
    print(teste);
    PriorityPrint(teste, 5);
    Pqueue_remove(teste);
    Pqueue_remove(teste);
    print(teste);
}