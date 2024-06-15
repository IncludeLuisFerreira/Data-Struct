#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct _value Val;
typedef struct _stack Stack;

Stack *init_Stack();
Val *create_valNode(int value);
bool is_stack_empty(Stack *stack);
void push(Stack *stack, int val);
void pop(Stack *stack);
void print_Stack(Stack *stack);


#endif