#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**************************************************************** PRIVATE STRUCT ****************************************************************/
struct _value {
    int value;
    struct _value *next;
};

struct _stack {
    Val *top;
    size_t size;
};

typedef struct _char {
    char caracter;
    struct _char *next;
}charnode;

typedef struct _charstack {
    charnode *top;
    size_t size;
}charstack;

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

int pop(Stack *stack) {
    if (is_stack_empty(stack)) {
        fprintf(stderr, "Pop not allowed in an EMPTY LIST!\n");
    }
    
    Val *node = stack->top;
    stack->top = node->next;
    int key = node->value;

    free(node);
    stack->size--;
    return key;
}

void print_Stack(Stack *stack) {
    if (is_stack_empty(stack)) {
        fprintf(stderr, "Trying to print an EMPTY LIST!\n");
        return ;
    }
    
    printf("Top ");
    for (Val *node = stack->top; node != NULL; node = node->next) {
        printf("\n%d\n", node->value);
    }
}

int peek_stack(Stack *stack) {
    if (is_stack_empty(stack)) {
       fprintf(stderr, "Error in peek_stack ==> Trying to peek an EMPTY LIST!\n");
    }
    else {
        return stack->top->value;
    }
}

void destroy_stack(Stack **stack_ref) {
    if (!is_stack_empty(*stack_ref)) {
        Val *node = (*stack_ref)->top;
        Val *next = NULL;

        while (node != NULL) {
            next = node->next;
            free(node);
            node = next;
        } 
    }
    free(*stack_ref);
    *stack_ref = NULL;
}

void initCharStack(charstack *stack) {
    stack->size = 0;
    stack->top = NULL;
}

void pushCharStack(charstack *stack, char c) {
    charnode *new_node = (charnode*) malloc(sizeof(charnode));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    
    new_node->caracter = c;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

char popCharStack(charstack *stack) {
    if (stack->top) {
        char c = stack->top->caracter;
        charnode *remove = stack->top;
        stack->top = stack->top->next;
        free(remove);
        return c;
    }
}

void print_charStack(charstack *stack) {
    if (!stack) {
        return ;
    }
    
    for (charnode *aux = stack->top; aux != NULL; aux = aux->next) {
        printf("%c ", aux->caracter);
    }
}

int isOperator(char c) {
    return (c == '+' || c == '*' || c == '/' || c == '-');
}

int RPNCalculatorOperator(char c, int n1, int n2) {
    switch (c)
    {
    case '+':
        return n1 + n2;
        break;
    case '-':
        return n1 - n2;
        break;
    case '*':
        return n1 * n2;
        break;
    case '/':
        return n1 / n2;
        break;
    }
}

int RPNCalculator(char *exp) {
    Stack stack; stack.top = NULL, stack.size = 0;
    int i = 0;

    while (exp[i] != '\0') {
        if (isOperator(exp[i])) {
            int n1 = pop(&stack);
            int n2 = pop(&stack);
            int result = RPNCalculatorOperator(exp[i], n2, n1);
            push(&stack, result); 
        }

        else {
            if (exp[i] != ' ')
                push(&stack, exp[i] - '0');
        }   
        i++;
    }
    return pop(&stack);
}

int isExpressionBalancedUtil(char c) {
   switch (c)
   {
    case '(':
    case '{':
    case '[':
        return 1;
        break;
   
    case ')':
    case '}':
    case ']':
        return 0;
        break;
   }
}

int checkOperator(char c, char s) {
    switch (c)
    {
    case '(':
        return s == ')';
        break;
    case '[':
        return s == ']';
        break;
    case '{':
        return s == '}';
        break;
    }
}

int isExpressionBalanced(char *exp) {
    charstack stack;
    stack.size = 0, stack.top = NULL;
    int i = 0;

    while (exp[i] != '\0') {
        if (isExpressionBalancedUtil(exp[i]) == 1) {
           pushCharStack(&stack, exp[i]);
        }
        else if (isExpressionBalancedUtil(exp[i]) == 0){
            if (stack.top) {
                char result = popCharStack(&stack);
                if (!checkOperator(result, exp[i])) {
                    return 0;
                }
            }
            else
                return 0;
        }
        i++;
    }
    return 1;
}


char* invertString(char *string) {
    if (!string) {
        return NULL;
    }

    charstack stack;
    stack.size = 0, stack.top = NULL;
    int i = 0;
    
    char *inverted = (char*) calloc(strlen(string), sizeof(char));

    while (string[i] != '\0') {
        pushCharStack(&stack, string[i]);
        i++;
    }

    print_charStack(&stack);
    
    i = 0;
    while (stack.top != NULL) {
        inverted[i] = popCharStack(&stack);
        i++;
    }

    inverted[strlen(string)] = '\0';
    return inverted;    
}

int isPalindrome(char *string) {
    if (!string)
        return 0;
        
    charstack stack;
    stack.size = 0, stack.top = NULL;
    int i = 0;
    
    while (string[i] != '\0') {
        pushCharStack(&stack, string[i]);
        i++;
    }

    int j = 0;
    while (stack.top != NULL) {
        char carac = popCharStack(&stack);
        
        if (carac != string[j])
            return 0;
        
        j++;
    }
    return 1;
}

int higherNumber(Stack *stack) {
    if (!stack->top) {
        return -999;
    }

    Val *node = stack->top;
    int higher = node->value;
    
    for (; node != NULL; node = node->next) {
        if (node->value > higher) {
            higher = node->value;
        }
    }
    return higher;
}

int stackcmp(Stack *stack1, Stack *stack2) {
    if (stack1->size > stack2->size)
        return stack1->size - stack2->size;
    else if (stack1->size < stack2->size)
        stack2->size - stack1->size;
    else
        return 0;
}

void stackcpy(const Stack *stack1, Stack *stack2) {
    if (!stack1->top) {
        destroy_stack(&stack2);
        stack2 = init_Stack();
    }

    Stack temp;
    temp.size = 0, temp.top = NULL;

    for (Val *node = stack1->top; node != NULL; node = node->next) {
        push(&temp, node->value);
    }

    while (temp.top != NULL) {
        push(stack2, pop(&temp));
    }
}

void stackinvert(Stack *stack) {
    if (!stack->top || stack->size < 2)
        return ;

    int tam = stack->size;
    int vetor[tam];

    int i = 0;
    for (Val *node = stack->top; node != NULL; node = node->next, i++) {
        vetor[i] = node->value;
    }

    destroy_stack(&stack);
    stack = init_Stack();
    
    for (int j = 0; j < tam; j++) {
        push(stack, vetor[j]);
    }
}

int countOddNumbers(const Stack *stack) {
    if (!stack->top) {
        return 0;
    }

    int count = 0;
    for (Val *node = stack->top; node != NULL; node = node->next) {
        if (node->value&1)
            count++;
    }
    return count;
}

int countEvenNumbers(const Stack *stack) {
    if (!stack->top) {
        return 0;
    }

    int count = 0;
    for (Val *node = stack->top; node != NULL; node = node->next) {
        if (node->value&1 == 0)
            count++;
    }
    return count;
}

