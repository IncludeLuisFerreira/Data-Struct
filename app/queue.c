#include "../include/queue.h"
#include <sys/time.h>
#include <stdlib.h>

int main() {
    Queue *test = init_queue();
    srand(time(NULL));
    
   /******** ENQUEUE/DEQUEUE TEST ********/

   for (int i = 0; i < 100; i++)
        enqueue(test, rand() % 100);
    
    for (int i = 0; i < 100; i++)
        dequeue(test);

    /*********************************** */
    
    
    
    
    destroy_queue(&test);
    
    print_queue(test);
    return 0;
}