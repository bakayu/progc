/*
Balanced Parenthesis

Check for balanced parentheses in an expression.

Given a string expression, write a program to examine whether the pairs of
"{",}","(",")","[","]" are correct in expression in O(N) time.

Constraints 0 < Length(expression) <= 30

Input 1 [()]{}{()()}

Output 1 true

Input 2 [()

Output 2 false
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Stack;

Stack *createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = 4;
    stack->data = (int *)malloc(sizeof(int) * stack->capacity);
    stack->size = 0;
    return stack;
}

bool is_empty(Stack *stack) { return stack->size == 0; }

void push_to_stack(Stack *stack, int val) {
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        stack->data =
            (int *)realloc(stack->data, sizeof(int) * stack->capacity);
    }

    stack->data[stack->size] = val;
    stack->size++;
}

// NOTE: Caller is responsible for underflow check,
// Calling on empty stack will result in undefined behaviour.
int peek(Stack *stack) { return stack->data[stack->size - 1]; }

// NOTE: Caller is responsible for underflow check,
// Calling on empty stack will result in undefined behaviour.
int pop_from_stack(Stack *stack) {
    int top = peek(stack);
    stack->size--;
    return top;
}

void cleanup(Stack *stack) {
    free(stack->data);
    free(stack);
}

bool is_balanced(const char *input) {
    Stack *stack = createStack();
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            push_to_stack(stack, ch);
        } else if (ch == ')' && !is_empty(stack) && peek(stack) == '(') {
            pop_from_stack(stack);
        } else if (ch == '}' && !is_empty(stack) && peek(stack) == '{') {
            pop_from_stack(stack);
        } else if (ch == ']' && !is_empty(stack) && peek(stack) == '[') {
            pop_from_stack(stack);
        } else {
            cleanup(stack);
            return false;
        }
    }

    bool result = is_empty(stack);
    cleanup(stack);
    return result;
}

int main(void) {
    const char *test_case_1 = "[()]{}{()()}";
    const char *test_case_2 = "[()";

    printf("test case 1: %s\n", is_balanced(test_case_1) ? "PASS" : "FAIL");
    printf("test case 2: %s\n", !is_balanced(test_case_2) ? "PASS" : "FAIL");

    return 0;
}
