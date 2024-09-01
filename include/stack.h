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
int pop(Stack *stack);
void print_Stack(Stack *stack);
int peek_stack(Stack *stack);
int RPNCalculator(char *exp);
int isExpressionBalanced(char *exp);
char* invertString(char *string);
int isPalindrome(char *string);
void stackcpy(const Stack *stack1, Stack *stack2);
void stackinvert(Stack *stack);
int countOddNumbers(const Stack *stack);

#endif