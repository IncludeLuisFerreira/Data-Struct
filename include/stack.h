#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct _value Val;
typedef struct _stack Stack;

Stack *init_Stack();
Val *create_valNode(int value);
void destroy_stack(Stack **stack_ref);
bool is_stack_empty(Stack *stack);
void push(Stack *stack, int val);
void pop(Stack *stack);
void print_Stack(Stack *stack);
int peek_stack(Stack *stack);

#endif