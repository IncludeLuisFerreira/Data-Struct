#include "../include/stack.h"

#include <stdlib.h>
#include <stdio.h>

/****************************************************************** PRIVATE STRUCT ******************************************************************/
struct _value {
    int value;
    struct _value *next;
};

struct _stack {
    Val *top;
    size_t size;
};

/**************************************************************************************************************************************************/

Stack *init_Stack() {
    Stack *stack = (Stack*) malloc(sizeof(stack));

    if (stack == NULL) {
        fprintf(stderr, "Heap memory is full");
        exit(EXIT_FAILURE);
    }
    stack->size = 0;
    stack->top = NULL;
    return stack;
}

Val *create_valNode(int value) {
    Val *node = (Val*) malloc(sizeof(Val));

    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->value = value;
    return node;
}

bool is_stack_empty(Stack *stack) {
    return stack->top == NULL;
}


void push(Stack *stack, int val) {
    Val *node = create_valNode(val);
    
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

void pop(Stack *stack) {
    if (is_stack_empty(stack)) {
        fprintf(stderr, "Pop not allowed in an EMPTY LIST!\n");
    }
    
    Val *node = stack->top;
    stack->top = node->next;

    free(node);
    stack->size--;
}

void print_Stack(Stack *stack) {
    if (is_stack_empty(stack)) {
        fprintf(stderr, "Trying to print an EMPTY LIST!\n");
    }
    
    printf("Top ");
    for (Val *node = stack->top; node != NULL; node = node->next) {
        printf("\n%d\n", node->value);
    }
}

