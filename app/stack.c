#include "stack.h"

int main() {

    Stack *origin = init_Stack();
    Stack *dest = init_Stack();
    Stack *vazia = init_Stack();

    push(origin, 1);
    push(origin, 5);
    push(origin, 10);

    stackcpy(origin, dest);
    printf("Origem: \n");
    print_Stack(origin);
    printf("Destino: \n");
    print_Stack(dest);


    stackinvert(origin);
    printf("Origin invertido: \n");
    print_Stack(origin);

    push(vazia, 1);
    stackinvert(vazia);
    print_Stack(vazia);
    return 0;
}