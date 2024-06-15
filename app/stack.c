#include "../include/stack.h"

int main() {
    Stack *teste = init_Stack();
    for (int i = 0; i < 10; i++)
        push(teste, i);

    print_Stack(teste);

    return 0;
}