#include "../include/stack.h"
#include <stdio.h>

int main() {
    Stack *teste = init_Stack();
    for (int i = 0; i < 10; i++)
        push(teste, i);

    print_Stack(teste);
    pop(teste);
    printf("%d",peek_stack(teste));
    pop(teste);
    print_Stack(teste);

    destroy_stack(&teste);
    
    

    return 0;
}